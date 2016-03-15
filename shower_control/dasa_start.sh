#!/bin/bash
pocketsphinx_continuous -jsgf dasa.gram  -dict dasa_simple.dic -samprate 16000 -inmic yes 2> err.txt | ./dasa_control
