import json
import os

import pandas as pd
import numpy as np
import os
import math
import tensorflow as tf
from tensorflow.keras.models import Sequential, Model, load_model
from tensorflow.keras.layers import Dense, Dropout, LSTM, BatchNormalization, Bidirectional
from sklearn.utils import shuffle
from sklearn.preprocessing import MinMaxScaler, StandardScaler

"""
Load existing configuration file
"""
def openJson(path):
	with open(path) as jsonFile:
		jsonObject = json.load(jsonFile)
		jsonFile.close()
	return jsonObject


"""
Overwrite configuration file with new json object
"""
def writeJson(jsonObject, path):
	with open(path, 'w') as jsonFile:
		json.dump(jsonObject, jsonFile, indent=4, sort_keys=True)
		jsonFile.close()

"""
Load default confignuration
"""
def defaultParams():
	jsonDefault = {
		'gpu': False,
		'epoch': 200,
		'dynamic_timestep' : 100,
		'max_scales' : 
		[],
		'min_scales' : 
		[],
		'model_directory' : './TrainedModel',
		'dataset_directory': './Dataset',
		'num_features' : 31,
		'sliding_rate' : 10,
		'timestep' : 60,
		'demo': False,
		'serve_command': ''
	}

	return jsonDefault

"""
Load configuration information
""" 
def loadParams(path):
	jsonObject = {}
	if os.path.exists(path):
	    jsonObject = openJson(path)
	else:# create configuration file with default values
	    jsonObject = defaultParams()
	    writeJson(jsonObject, path) 
	    
	return jsonObject

"""
Scale data using MinMax scaler
"""
def scale_data(data, min_max_scaler):
    for i in range(len(data)):
        data[i] = min_max_scaler.transform(data[i])
    return data

"""
Load dataset and find corrupt samples(NaN, incorrect shape). Incorrect shape can be fixed to a degree
"""
def loadDataset(dataset_directory, timestep, num_features):

	x_train = []
	y_train = []

	files = os.listdir(dataset_directory)

	for i in files:
		samples = os.listdir(dataset_directory + '/' + i)
		num_tests = len(samples);
		shuffle(samples, random_state = 0) #eliminates any order information

		for k in range(0, num_tests):
			df = pd.read_csv(dataset_directory+ '/' + i + '/' + samples[k], header=None, sep=' ')
			df = df.drop(df.index[timestep:]) #possible bad parsing of separator, rows beyond timestep value
			if len(df.columns) > num_features: ##possible bad parsing of separator, columns beyond timestep value
				df = df.drop(columns=[num_features:])

			if df.isnull().values.any() or len(np.where(df.applymap(np.isreal).all(1)==False)[0]) > 0: #very inefective solution, shall be fixed in the future
				print(f'Found NaN value at gesture[{i}] index [{samples[k]}], sample is thrown away')
				continue


			x_train.append(df.to_numpy())
			y_train.append(int(i))

		print(f'Finished gesture type [{i}]')
	x_train = np.array(x_train)
	y_train = np.array(y_train)

	print("x_train.shape: ", x_train.shape)
	print("y_train.shiape: ", y_train.shape)
	return x_train, y_train, len(files)
"""
Define model architeture
"""
def model_architecture(timestep, num_classes,in_shape):
	model = Sequential()
	model.add(Bidirectional(LSTM(units=timestep, return_sequences=True ,dtype='float64'),input_shape=in_shape,dtype='float64'))
	model.add(BatchNormalization())
	model.add(Dropout(0.6))

	model.add(Bidirectional(LSTM(units=timestep ,dtype='float64') ,dtype='float64'))
	model.add(BatchNormalization())
	model.add(Dropout(0.6))

	model.add(Dense(num_classes, activation='softmax',dtype='float64'))
	model.summary()

	return model

def main():

	writepath = './gestureLeapConfig.json'
	params = loadParams(writepath)

	if params['gpu']: #run training with GPU support, requires Nvidia's CUDA
		physical_devices = tf.config.list_physical_devices('GPU')
		tf.config.experimental.set_memory_growth(physical_devices[0], enable=True)
	x_train = []
	y_train = []

	x_train, y_train, num_classes = loadDataset(params['dataset_directory'], params['timestep'], params['num_features'])

	min_max_scaler = MinMaxScaler(feature_range=(0,1))

	num_instances, timestep, num_features = x_train.shape
	x_train = np.reshape(x_train, newshape=(-1, num_features))
	x_train = min_max_scaler.fit_transform(x_train)
	x_train = np.reshape(x_train, newshape=(num_instances, timestep, num_features))

	x_train, y_train = shuffle(x_train, y_train, random_state=0)

	model = model_architecture(timestep, num_classes, x_train.shape[1:])

	opt = tf.keras.optimizers.Adam(learning_rate=0.0001, decay=1e-5)
	model.compile(
		loss='sparse_categorical_crossentropy',
		optimizer=opt,
		metrics=['accuracy'],
	)

	gestures = model.fit(x = x_train,
		y = y_train,
		epochs=params['epoch'],
		batch_size=24,
		shuffle=True
	) #train model

	params['max_scales'] = min_max_scaler.data_max_.astype('float64').tolist()
	params['min_scales'] = min_max_scaler.data_min_.astype('float64').tolist()

	params['timestep'] = timestep
	params['num_features'] = num_features
	
	params['serve_command'] = 'serving_default_' + model.input.name

	writeJson(params, writepath)	

	model.save(params['model_directory'], save_format='tf')

if __name__ == '__main__':
	main()