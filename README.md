# Gesture-classification

This library was developed as a bachelor thesis at FIT CTU in Prague by Anh Tran Viet.

The library allows user to sample their own hand gesture dataset, using `DataSampler.exe`, fit their model, using `model_training.py`, and apply it in real-time recognition using provided demo application `GestureLeap.exe`.

The data sampling and real-time deployment are written in C++. The model training is in the form of a Python script.

## DataSampler
The DataSampler application serves for sampling custom datasets using predefined feature extraction methods.

The application loads its configuration from `gestureLeapConfig.json` in the execution folder. The user can change `dataset_directory`, `timestep`, `dynamic_timestep` values, or use default values. If the configuration file is not found, it gets created with default values.

The user is on startup asked to enter gesture type, must be a numeric value. Samples are saved to `<dataset directory>/<gesture type>/<index>.txt`. The index value begins from 0, but can be changed in application using `reinit <gesture type> <index>` command. Call `help` command to get the list of available commands.

If you receive `Error opening a file`, try disabling antivirus
#### Available functionalities
* help - *list of commands*
* close - *close application*
* record - *begin sampling*
* open - *begin continuous sampling*
* pause - *pause open sampling*
* dynamic - *begin sampling for dynamic gestures, base on significant frames*
* reinit \<gesture type> \<index> - *set a new gesture type and starting file indexing*

## model_training.py

Follow *Setup* instructions down below before running.

The Python script serves for model training on custom datasets. Run `python model_training.py`

The script loads its configuration from `gestureLeapConfig.json` in the execution folder. The user can change `dataset_directory`, `model_directory`, `epoch`, `dynamic_timestep`, `gpu` values, or use default values. If the configuration file is not found, it gets created with default values. Dataset directory must follow structure defined by DataSampler application `<dataset_directory>/<gesture type>/<index>.txt`. Names of gesture types must be numeric values. The `model_directory` is the location where the trained model will be saved, must exist.

 Set `gpu: True` to run the script with GPU support, more on installation [here](https://www.tensorflow.org/install/gpu)


## GestureApp
GestureApp application serves for demonstration of the thesis.

The application loads its configuration from `gestureLeapConfig.json` in the execution folder. The user can change `model_directory`, `sliding_rate` values, or use default values. Other configuration values should be in relation to pre-trained model yield by `model_training.py`. If the configuration file is not found, it gets created with default values, which could lead to exceptions/crashes caused by incorrect configuration.

Application classifies gestures once a hand is presented in Leap Motion's field of view.

Call `help` command to get the list of available commands.

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
│   │   ├── DataSampler
│   │   │   ├── DataSampler.vcx.proj
│   │   │   └── ...
│   │   └── DataSampler.sln
│   ├── Dataset
│   │   ├── ASLDataset
│   │   |   ├── Samples
│   │   │   │   ├── gestures_test.csv
│   │   │   │   └── gestures_train.csv
│   │   │   ├── optimal_dropout.ipynb
│   │   │   ├── optimal_layers.ipynb
│   │   │   └── ...
│   │   ├── DataCollection
│   │   │   └── ...
│   ├── GestureApp
│   │   ├── GestureClassificationThesis.sln
│   │   ├── GestureApp.vcx.proj
│   │   └── ...
│   ├── TrainingScript
│   │   ├── model_training.ipynb
│   │   ├── model_training.py
│   │   └── ...
│   ├── includes
│   │   └── ...
│   └── ...
└── text
    └── ...

```

### src
The directory contains the source codes of the project. Include `GestureClassificationThesis.sln` solution. The solution includes the GestureApp project as well as the DataSampler project. Both projects are ready to run in Debug x64 mode and Release x64 mode. The default startup project is GestureApp. Switching requires the user to manually right click DataSampler project and select `Set as Startup Project`.

The Dataset directory contains ASLDataset and our custom dataset stored in DataCollection. ASLDataset includes Jupyter notebooks used for finetuning hyperparameters and their sample files.

The includes directory has all necessary libraries and APIs to debug the solution.

The src directory also contains `model_training.ipynb` Jupyter notebook and `model_training.py` script. The Jupyter notebook is used mainly for experimental purposes either in the local environment or in Google Colab. For model training, use its `model_training.py`, which loads user parameters from the configuration file or uses default values.

## Setup
[Anaconda](https://anaconda.org) package manager is suggested to manage required frameworks.
It is not needed, but the setup is described with the usage of Anaconda.
Instalation guide can be found [here](https://conda.io/projects/conda/en/latest/user-guide/install/index.html).

To create a new conda environment and install all dependencies, just save the following config as ``environment.yml`` or use created one. 
```
name: gestureleap
channels:
  - conda-forge
  - defaults
dependencies:
  - _tflow_select=2.3.0=gpu
  - absl-py=0.11.0=py38haa244fe_0
  - aiohttp=3.7.3=py38h294d835_2
  - argon2-cffi=20.1.0=py38h294d835_2
  - astor=0.8.1=pyh9f0ad1d_0
  - astunparse=1.6.3=pyhd8ed1ab_0
  - async-timeout=3.0.1=py_1000
  - async_generator=1.10=py_0
  - attrs=20.3.0=pyhd3deb0d_0
  - backcall=0.2.0=pyh9f0ad1d_0
  - backports=1.0=py_2
  - backports.functools_lru_cache=1.6.1=py_0
  - bleach=3.3.0=pyh44b312d_0
  - blinker=1.4=py_1
  - brotlipy=0.7.0=py38h294d835_1001
  - ca-certificates=2020.12.5=h5b45459_0
  - cachetools=4.2.1=pyhd8ed1ab_0
  - certifi=2020.12.5=py38haa244fe_1
  - cffi=1.14.5=py38hd8c33c5_0
  - chardet=3.0.4=py38h9bdc248_1008
  - click=7.1.2=pyh9f0ad1d_0
  - colorama=0.4.4=pyh9f0ad1d_0
  - cryptography=3.4.4=py38hb7941b4_0
  - cycler=0.10.0=py_2
  - decorator=4.4.2=py_0
  - defusedxml=0.6.0=py_0
  - entrypoints=0.3=pyhd8ed1ab_1003
  - freetype=2.10.4=h546665d_1
  - google-auth=1.24.0=pyhd3deb0d_0
  - google-auth-oauthlib=0.4.1=py_2
  - google-pasta=0.2.0=pyh8c360ce_0
  - h5py=2.10.0=nompi_py38h6053941_105
  - hdf5=1.10.6=nompi_h5268f04_1114
  - icu=68.1=h0e60522_0
  - idna=2.10=pyh9f0ad1d_0
  - importlib-metadata=3.4.0=py38haa244fe_0
  - importlib_metadata=3.4.0=hd8ed1ab_0
  - intel-openmp=2020.3=h57928b3_311
  - ipykernel=5.5.0=py38hc5df569_1
  - ipython=7.20.0=py38hc5df569_2
  - ipython_genutils=0.2.0=py_1
  - ipywidgets=7.6.3=pyhd3deb0d_0
  - jedi=0.18.0=py38haa244fe_2
  - jinja2=2.11.3=pyh44b312d_0
  - joblib=1.0.1=pyhd8ed1ab_0
  - jpeg=9d=h8ffe710_0
  - jsonschema=3.2.0=py_2
  - jupyter=1.0.0=py38haa244fe_6
  - jupyter_client=6.1.11=pyhd8ed1ab_1
  - jupyter_console=6.2.0=py_0
  - jupyter_core=4.7.1=py38haa244fe_0
  - jupyterlab_pygments=0.1.2=pyh9f0ad1d_0
  - jupyterlab_widgets=1.0.0=pyhd8ed1ab_1
  - keras-applications=1.0.8=py_1
  - keras-preprocessing=1.1.2=pyhd8ed1ab_0
  - kiwisolver=1.3.1=py38hbd9d945_1
  - krb5=1.17.2=hbae68bd_0
  - lcms2=2.12=h2a16943_0
  - libblas=3.9.0=8_mkl
  - libcblas=3.9.0=8_mkl
  - libclang=11.0.1=default_h5c34c98_1
  - libcurl=7.71.1=h4b64cdc_8
  - liblapack=3.9.0=8_mkl
  - libpng=1.6.37=h1d00b33_2
  - libprotobuf=3.15.1=h7755175_0
  - libsodium=1.0.18=h8d14728_1
  - libssh2=1.9.0=hb06d900_5
  - libtiff=4.2.0=hc10be44_0
  - lz4-c=1.9.3=h8ffe710_0
  - m2w64-gcc-libgfortran=5.3.0=6
  - m2w64-gcc-libs=5.3.0=7
  - m2w64-gcc-libs-core=5.3.0=7
  - m2w64-gmp=6.1.0=2
  - m2w64-libwinpthread-git=5.0.0.4634.697f757=2
  - markdown=3.3.3=pyh9f0ad1d_0
  - markupsafe=1.1.1=py38h294d835_3
  - matplotlib=3.3.4=py38haa244fe_0
  - matplotlib-base=3.3.4=py38h34ddff4_0
  - mistune=0.8.4=py38h294d835_1003
  - mkl=2020.4=hb70f87d_311
  - msys2-conda-epoch=20160418=1
  - multidict=5.1.0=py38h294d835_1
  - nbclient=0.5.2=pyhd8ed1ab_0
  - nbconvert=6.0.7=py38haa244fe_3
  - nbformat=5.1.2=pyhd8ed1ab_1
  - nest-asyncio=1.4.3=pyhd8ed1ab_0
  - notebook=6.2.0=py38haa244fe_0
  - numpy=1.19.5=py38h0cc643e_1
  - oauthlib=3.0.1=py_0
  - olefile=0.46=pyh9f0ad1d_1
  - openssl=1.1.1j=h8ffe710_0
  - opt_einsum=3.3.0=py_0
  - packaging=20.9=pyh44b312d_0
  - pandas=1.2.2=py38h4c96930_0
  - pandoc=2.11.4=h8ffe710_0
  - pandocfilters=1.4.2=py_1
  - parso=0.8.1=pyhd8ed1ab_0
  - patsy=0.5.1=py_0
  - pickleshare=0.7.5=py_1003
  - pillow=8.1.0=py38h9273828_2
  - pip=21.0.1=pyhd8ed1ab_0
  - prometheus_client=0.9.0=pyhd3deb0d_0
  - prompt-toolkit=3.0.16=pyha770c72_0
  - prompt_toolkit=3.0.16=hd8ed1ab_0
  - protobuf=3.15.1=py38h885f38d_0
  - pyasn1=0.4.8=py_0
  - pyasn1-modules=0.2.7=py_0
  - pycparser=2.20=pyh9f0ad1d_2
  - pygments=2.8.0=pyhd8ed1ab_0
  - pyjwt=2.0.1=pyhd8ed1ab_0
  - pyopenssl=20.0.1=pyhd8ed1ab_0
  - pyparsing=2.4.7=pyh9f0ad1d_0
  - pyqt=5.12.3=py38haa244fe_7
  - pyqt-impl=5.12.3=py38h885f38d_7
  - pyqt5-sip=4.19.18=py38h885f38d_7
  - pyqtchart=5.12=py38h885f38d_7
  - pyqtwebengine=5.12.1=py38h885f38d_7
  - pyreadline=2.1=py38haa244fe_1003
  - pyrsistent=0.17.3=py38h294d835_2
  - pysocks=1.7.1=py38haa244fe_3
  - python=3.8.8=h7840368_0_cpython
  - python-dateutil=2.8.1=py_0
  - python_abi=3.8=1_cp38
  - pytz=2021.1=pyhd8ed1ab_0
  - pywin32=300=py38h294d835_0
  - pywinpty=0.5.7=py38h32f6830_1
  - pyzmq=22.0.3=py38h7a0e47e_0
  - qt=5.12.9=h5909a2a_4
  - qtconsole=5.0.2=pyhd8ed1ab_0
  - qtpy=1.9.0=py_0
  - requests=2.25.1=pyhd3deb0d_0
  - requests-oauthlib=1.3.0=pyh9f0ad1d_0
  - rsa=4.7.1=pyh44b312d_0
  - scikit-learn=0.24.1=py38ha09990b_0
  - scipy=1.6.0=py38h5f893b4_0
  - seaborn=0.11.1=hd8ed1ab_1
  - seaborn-base=0.11.1=pyhd8ed1ab_1
  - send2trash=1.5.0=py_0
  - setuptools=49.6.0=py38haa244fe_3
  - six=1.15.0=pyh9f0ad1d_0
  - sqlite=3.34.0=h8ffe710_0
  - statsmodels=0.12.2=py38h347fdf6_0
  - tensorboard=2.4.1=pyhd8ed1ab_0
  - tensorboard-plugin-wit=1.8.0=pyh44b312d_0
  - tensorflow=2.3.0=mkl_py38h8557ec7_0
  - tensorflow-base=2.3.0=eigen_py38h75a453f_0
  - tensorflow-estimator=2.4.0=pyh9656e83_0
  - termcolor=1.1.0=py_2
  - terminado=0.9.2=py38haa244fe_0
  - testpath=0.4.4=py_0
  - threadpoolctl=2.1.0=pyh5ca1d4c_0
  - tk=8.6.10=h8ffe710_1
  - tornado=6.1=py38h294d835_1
  - traitlets=5.0.5=py_0
  - typing-extensions=3.7.4.3=0
  - typing_extensions=3.7.4.3=py_0
  - urllib3=1.26.3=pyhd8ed1ab_0
  - vc=14.2=hb210afc_3
  - vs2015_runtime=14.28.29325=h5e1d092_3
  - wcwidth=0.2.5=pyh9f0ad1d_2
  - webencodings=0.5.1=py_1
  - werkzeug=1.0.1=pyh9f0ad1d_0
  - wheel=0.36.2=pyhd3deb0d_0
  - widgetsnbextension=3.5.1=py38haa244fe_4
  - win_inet_pton=1.1.0=py38haa244fe_2
  - wincertstore=0.2=py38haa244fe_1006
  - winpty=0.4.3=4
  - wrapt=1.12.1=py38h294d835_3
  - xz=5.2.5=h62dcd97_1
  - yarl=1.6.3=py38h294d835_1
  - zeromq=4.3.3=h0e60522_3
  - zipp=3.4.0=py_0
  - zlib=1.2.11=h62dcd97_1010
  - zstd=1.4.8=h4e2f164_1
  - pip:
    - flatbuffers==1.12
    - gast==0.3.3
    - grpcio==1.32.0
    - opt-einsum==3.3.0
    - tensorflow-gpu==2.4.1

```

Run ``conda env create -f environment.yml``, and after the environment setup is complete, run ``conda activate gestureleap`` to activate it. 

Remove environment by `conda remove --name gestureleap --all`
