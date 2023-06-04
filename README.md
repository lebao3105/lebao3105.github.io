# lebao3105.github.io
My personal page lives again!

# How to read offline
First, go online and install ```Pelican[markdown]``` with pip first. Clone this repo.

Then you can go offline:)

"cd" to the cloned repository, run:
```bash
$ pelican content # Usually everything is up-to-date, run this will (re)generate all web pages
$ pelican --listen
```

Want to use ```make```? Here you go:)
```bash
$ make html
$ make serve
```

The website will be stored locally on ```localhost:8000```.

Enjoy!