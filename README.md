# Gesture-classification

This library was developed as a bachelor thesis at FIT CTU in Prague by Anh Tran Viet.

The library allows user to sample their own hand gesture dataset, using `DataSampler.exe`, fit their model, using `model_training.py`, and apply it in real-time recognition using provided demo application `GestureLeap.exe`.

The data sampling, and real-time deployment is written in C++. The model training is in form of Python script.

## DataSampler
DataSampler application serves for sampling custom dataset using predefined feature extraction methods.

The application loads its configuration from `gestureLeapConfig.json` in execution folder. The user can change `dataset_directory`, `timestep`, `dynamic_timestep` values, or use default values. If the configuration file is not found, it gets created with default values.

The user is on startup asked to enter gesture type, must be numeric value. Samples are saved to `<dataset directory>\<gesture type>\<index>.txt`. The index value begins from 0, but can be changed in application using `reinit <gesture type> <index>` command. Call `help` command to get list of available commands.

#### Available functionalities
* help - *list of commands*
* close - *close application*
* record - *begin sampling*
* open - *begin continuous sampling*
* pause - *pause open sampling*
* dynamic - *begin sampling for dynamic gestures, base on significant frames*
* reinit \<gesture type> \<index> - *set a new gesture type and starting file indexing*

## model_training.py

The Python scrips serves for model training on custom datasets. Run `python model_training.py`

The script loads its configuration from `gestureLeapConfig.json` in execution folder. The user can change `dataset_directory`, `model_directory`, `epoch`, `dynamic_timestep`, `gpu` values, or use default values. If the configuration file is not found, it gets created with default values. Dataset directory must follow structure defined by DataSampler application `<dataset_directory>/<gesture type>/<index>.txt`. Names of gesture types must be numeric values. The `model_directory` is location where the trained model will be saved, must exist.

 Set `gpu: True` to run the script with GPU support, more on installation at https://www.tensorflow.org/install/gpu


## GestureApp
GestureApp application serves for demonstration of the thesis.

The application loads its configuration from `gestureLeapConfig.json` in execution folder. The user can change `model_directory`, `sliding_rate` values, or use default values. Other configuration values should be in relation pre-trained model yield by `model_training.py`. If the configuration file is not found, it gets created with default values, which could lead to exceptions/crashes caused by incorrect configuration.

Application classifies gestures once a hand is presented in Leap Motion's field of view.

Call `help` command to get list of available commands.

#### Available functionalities
* help - *list of commands*
* close - *close application*
* calibrate - *calibrate sensors*
* merge - *merge data from calibrated sensors*
* stopMerge - *stop data merging*


## Directory structure
This directory consists of the pdf version of the bachelor thesis, text directory, src directory, executables folder, and conda environment configuration file.

* text directory - *LaTeX source files for the bachelor thesis*
* src directory - *source code and experimental Jupyter notebooks*
* executables directory - *executable files, python script, dataset, pre-trained model, application's configuration file*

```
.
├── README.md
├── thesis.pdf
├── environment.yml
├── executables
│   ├── Dataset
│   │   └── ...
│   ├── TrainedModel
│   │   └── ...
│   ├── DataSampler.exe
│   ├── model_training.py
│   ├── GestureApp.exe
│   ├── gestureLeapConfig.json
│   └── ...
├── src
│   ├── DataSampler
│   │   ├── DataSampler
│   │   │   ├── DataSampler.vcx.proj
│   │   │   └── ...
│   │   └── DataSampler.sln
│   ├── Dataset
│   │   ├── ASLDataset
│   │   |   ├── Samples
│   │   │   │   ├── gestures_test.csv
│   │   │   │   └── gestures_train.csv
│   │   │   ├── optimal_dropout.ipynb
│   │   │   ├── optimal_layers.ipynb
│   │   │   └── ...
│   │   ├── DataCollection
│   │   │   └── ...
│   ├── GestureApp
│   │   ├── GestureClassificationThesis.sln
│   │   ├── GestureApp.vcx.proj
│   │   └── ...
│   ├── includes
│   │   └── ...
│   ├── model_training.ipynb
│   ├── model_training.py
│   └── ...
└── text
    └── ...

```

### src
The directory contains source codes of the project. Include `GestureClassificationThesis.sln` solution. The solution includes GestureApp project as well as DataSampler project. Both projects are ready to be ran in Debug x64 mode, and Release x64 mode. Default startup project is GestureApp. Switching requires the user to manualy right click DataSampler project and select `Set as Startup Project`.

The Dataset directory contains ASLDataset and our custom dataset stored in DataCollection. ASLDataset includes Jupyter notebooks used for finetunning hyperparameters and its sample files.

The includes directory has all necessary libraries and API's to debug the solution.

The src directory also contains `model_training.ipynb` Jupyter notebook and `model_training.py` script. The Jupyter notebook used mainly for experimental purposes either in local environment or in Google Colab. For model training use its `model_training.py`, which loads user parameteres from configuration file or use default values.

## Setup
[Anaconda](https://anaconda.org) package manager is suggested to manage required frameworks.
It is not needed, but the setup is described with the usage of Anaconda.
Instalation guide can be found [here](https://conda.io/projects/conda/en/latest/user-guide/install/index.html).

To create new conda environment and install all dependencies just save following config as ``environment.yml`` or use created one.
```
name: GestureLeap
channels:
  - anaconda
  - conda-forge
  - defaults
dependencies:
  - python>=3.7
  - numpy=1.20
  - opencv=4.5.0
  - scipy=1.6.0
  - scikit-image=0.16.2
  - scikit-learn=0.24.1
  - pandas
  - tesseract
  - flask
  - pytest
  - jsonpickle
  - jupyter
  - natsort
  - pillow
  - pip
  - requests
  - yaml
  - seaborn
  - pip:
    - flask-restful
    - improutils
    - imutils
    - pytesseract
```

Then just run ``conda env create -f environment.yml`` (make sure that you have at least 3 GB of free space).
This will probably take a while (from 5 minutes to 40 or more minutes based on the speed of the computer).
After setting up the environment is done, just run ``conda activate iSophiEnv`` to activate it.
Setup was tested on macOS, but it should work just fine on Windows with anaconda prompt and ubuntu as well.
