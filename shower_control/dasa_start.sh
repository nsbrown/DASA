#!/bin/bash
pocketsphinx_continuous -jsgf dasa.gram  -dict dasa.dic -samprate 16000 -inmic yes 2> err.txt | ./dasa_controlssh
