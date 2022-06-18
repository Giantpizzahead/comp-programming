import time
import subprocess

def test_pin(pin):
    process = subprocess.Popen(['pin_checker'],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    inputdata = pin
    stdoutdata,stderrdata=process.communicate(input=inputdata)