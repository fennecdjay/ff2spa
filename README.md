ff2spa
============

----------------------

*draw sound!* :tada:

----------------------

[ff2spa](https://github.com/fennecdjay/ff2spa) read a [farbfeld](http://tools.suckless.org/farbfeld/) file from **stdin** and outputs a [spa](https://github.com/PaulBatchelor/Soundpipe/tree/master/lib/spa) file to **stdout**.

dependencies
------------

only the [soundpipe](https://github.com/PaulBatchelor/Soundpipe) header is needed to compile.  
however, this program migth be useless without [the former](http://github.com/PaulBatchelor/Soundpipe) and [farbfeld] (http://tools.suckless.org/farbfeld/)

build
-----

```
make
```

install
-------

```
make install
```

use
---

farbled2spa attemps to create a waveform from a drawing.  
So, for now, provide it a simple waveform, black on white.  
use pipes:

```
cat my_file.ff | ff2spa > my_file.spa
```
then you have a [spa](https://github.com/PaulBatchelor/Soundpipe/tree/master/lib/spa) ready to read for your [osc](http://paulbatchelor.github.io/res/soundpipe/docs/osc.html)


----------------------

Notes
-----

The only things needed in the [soundpipe](https://github.com/PaulBatchelor/Soundpipe) header
is the SPFLOAT definitions.  
So if you don't have/want [soundpipe](https://github.com/PaulBatchelor/Soundpipe),
you can use [this](https://gist.github.com/fennecdjay/4cf0cb9aac35470171d03f5ccf10b583)
and adjust it to your liking. (set SPFLOAT to **float** or **double** or maybe **long double**)
