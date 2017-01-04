Vending Machine
===============

Implements the Vending Machine Kata as prescribed by https://github.com/guyroyse/vending-machine-kata


About
-----

- Written in plain C99 so it could be theoretically run on a small microcontroller.
- Modular, almost to the point of being object-oriented.
- Designed with the mechanical limitations of a vending machine in mind.


Requirements
------------

- C Compiler (GCC and Clang are tested)
- GNU Make
- Ruby (for the [CMock](https://github.com/ThrowTheSwitch/CMock) and [Unity](https://github.com/ThrowTheSwitch/Unity) build processes)

If you're running on macOS, you will want to make sure Xcode is installed from the Mac App Store, then install the Xcode Command Line Utilities with a command like:

```
xcode-select --install
```


Cloning This Repository
-----------------------

This repository depends on Git submodules, so when you clone it, please make sure to do so recursively:

```
git clone --recursive https://github.com/alexmarkley/vending-machine.git
```


Building & Running Tests
------------------------

From the cloned project directory, type:

```
make
```

The build process should automatically proceed, with tests running and a test summary printing out at the end like so:

```

--------------------------
OVERALL UNITY TEST SUMMARY
--------------------------
78 TOTAL TESTS 0 TOTAL FAILURES 0 IGNORED

```

To see the details of every test, type:

```
cat build/test/*.result
```

Using the CLI
-------------

After building, the CLI can be launched by the following command:

```
build/vending-machine
```

You will see a prompt like the following:

```
Main: Welcome to the Vending Machine Demo Frontend. For help, see README.md.
CoinSlot: INSERT COIN
 > 
```

The vending machine is ready to accept user input. There are a few commands:

- **q** - Insert a Quarter
- **d** - Insert a Dime
- **n** - Insert a Nickel
- **p** - Insert a Penny
- **r** - Coin Return
- **1** - Select Cola
- **2** - Select Chips
- **3** - Select Candy
- **Q** - Quit

An example session might look like this:

```
Main: Welcome to the Vending Machine Demo Frontend. For help, see README.md.
CoinSlot: INSERT COIN
 > 3
Product: PRICE $0.65
CoinSlot: INSERT COIN
 > q
CoinSlot: $0.25
 > q
CoinSlot: $0.50
 > q
CoinSlot: $0.75
 > 3
CoinReturn: Dime Ejected
CoinSlot: INSERT COIN
Product: Vended Candy
 > Q
```

Thanks for taking a look. Have a great day!
