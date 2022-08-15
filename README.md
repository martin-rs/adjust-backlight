# Adjust Brightness

This program can be used to control the backlight on your GNU+Linux system (if
you're using intel integrated graphics).

Either set the $SCRIPTDIR environment variable or specify the desired PATH to where 
the program will be put after compilation in the Makefile.

#### Examples

Check the current value:
```sh
br
br status
```

Change the value:
```sh
br 1000
br +1000
br -1000
```

- To set a specific value use no symbol.
- To increment the value you can use the + symbol.
- To decrement the value you can use the - symbol.
