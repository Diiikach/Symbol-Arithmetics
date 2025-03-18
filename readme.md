# Symbol-Arithmetics
Symbol-Arithmetics is a library that allows you to compute some things 
within functions. <br>
You can easily create variables, substitute them to real values. Also you can get derivative of functions. <br>

### Usage
First of all you need to clone repo. Copy to clipboard next command: <br>
``
git clone https://github.com/Diiikach/Symbol-Arithmetics.git && make build
`` <br>

Now you have file named as _differentiator_. Below is shown example of usage:

``differentiator --eval “x * y“ x=10 y=12
``

``
differentiator --diff “x * sin(x)“ --by x
``

### Run tests
to run tests you need to install google test <br>
``
sudo apt-get install libgtest-dev
``

to run tests paste to terminal" <br>
``
make test
``