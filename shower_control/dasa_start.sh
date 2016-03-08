#!/bin/bash
pocketsphinx_continuous -lm dasa.lm -dict dasa.dic -samprate 16000 -inmic yes 2> err.txt | ./dasa_control
