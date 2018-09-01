## Installation

The examples are built upon `xtensor-python`, we highly recommend to install it with conda:
`conda install xtensor-python -c quantstack -c conda-forge`.

The notebooks require additional packages for data visualization:

- ipywidgets
- bqplot
- ipyvolume

They can be installed with conda too:

`conda install ipywidgets bqplot ipyvolume -c conda-forge`

## Building the examples

To build an example, go to its directory and run:

`pip install ./`

This will build the extension module and install it in your conda environment. If you
plan to change it and build it many times, it's better to install it in dev mode:

`pip install -e ./`

Otherwise you have to change the build number to avoid pip complaining that the extension
is already installed.

On Windows, symbolic links are not supported, thus the development mode does not change anything,
so you have either to bump the build number of to manually remove the files from
`$(CONDA_ENV)/Lib/site-packages`. For each extension there is a `.pyd` file and a `.egg-info`
folder to remove.

