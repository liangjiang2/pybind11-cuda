cd pydemo && mkdir build
cd build && cmake .. && make
cd ../../
python3 setup.py sdist
pip install dist/pydemo-*.tar.gz
