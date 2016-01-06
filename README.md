PONG - "ncurses" version - BETA
===============================

***VERSION***

`0.6.1`

***Build***

`make`

You can run this from the local `bin` directory via: `./bin/pong` 


***Install***

`make install` (Or, depending on your permissions, `sudo make install`

This will install `pong` to `/usr/local/bin/`. Update your executable path as needed.

At this point, you may want to clean your local build files:

`make clean`

***Testing***


`make test`

This will run Valgrind tests while the program is executing (defaults to `valgrind ./bin/pong --leak-check=full -v` (See `Makefile` for more info...)

***Uninstall***

So, this version of Pong wasn't your cup of tea? Well, that's fine, I suppose. Just run the following command and you will be rid of it for good! :-)

`make uninstall`

***Documentation***

As the code continues to grow, so will the documentation should it be formatted correctly. To generate the latest version of the docs, simply run:

`doxygen Doxyfile`

## Dependencies

- [ncurses](https://www.gnu.org/software/ncurses/) - ncurses ("new" curses - be sure to install `ncurses.h` - Many Debian/Ubuntu-based  *Linux* distros package this in libncurses-dev)
- [Valgrind](http://valgrind.org/) - Instrumentation Framework
- [Doxygen](http://www.stack.nl/~dimitri/doxygen/) - Documentation

-- JUSTIN R. EVANS --

jurevans@gmail.com

http://fullstackconsultancy.net/

Additional Notes
================

File structure:

```
.
|── Doxyfile
├── Makefile
├── README.md
├── bin
│   ├── pong
│   └── pong.dSYM
│       └── Contents
│           ├── Info.plist
│           └── Resources
│               └── DWARF
│                   └── pong
├── docs
│   ├── html
│   │   ├── arrowdown.png
│   │   ├── arrowright.png
│   │   ├── bc_s.png
│   │   ├── bdwn.png
│   │   ├── closed.png
│   │   ├── doc.png
│   │   ├── doxygen.css
│   │   ├── doxygen.png
│   │   ├── dynsections.js
│   │   ├── folderclosed.png
│   │   ├── folderopen.png
│   │   ├── index.html
│   │   ├── jquery.js
│   │   ├── md__r_e_a_d_m_e.html
│   │   ├── nav_f.png
│   │   ├── nav_g.png
│   │   ├── nav_h.png
│   │   ├── open.png
│   │   ├── pages.html
│   │   ├── search
│   │   │   ├── all_0.html
│   │   │   ├── all_0.js
│   │   │   ├── close.png
│   │   │   ├── mag_sel.png
│   │   │   ├── nomatches.html
│   │   │   ├── pages_0.html
│   │   │   ├── pages_0.js
│   │   │   ├── search.css
│   │   │   ├── search.js
│   │   │   ├── search_l.png
│   │   │   ├── search_m.png
│   │   │   ├── search_r.png
│   │   │   └── searchdata.js
│   │   ├── splitbar.png
│   │   ├── sync_off.png
│   │   ├── sync_on.png
│   │   ├── tab_a.png
│   │   ├── tab_b.png
│   │   ├── tab_h.png
│   │   ├── tab_s.png
│   │   └── tabs.css
│   └── latex
│       ├── Makefile
│       ├── doxygen.sty
│       ├── md__r_e_a_d_m_e.tex
│       └── refman.tex
├── lib
├── src
│   ├── ball.c
│   ├── field.c
│   ├── include
│   │   ├── ball.h
│   │   ├── field.h
│   │   ├── paddle.h
│   │   ├── screen.h
│   │   └── user.h
│   ├── obj
│   │   ├── ball.o
│   │   ├── field.o
│   │   ├── paddle.o
│   │   ├── screen.o
│   │   └── user.o
│   ├── paddle.c
│   ├── pong.c
│   ├── screen.c
│   └── user.c
└── tests
    └── TESTS.md

```

Enjoy!
