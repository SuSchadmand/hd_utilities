#!/usr/bin/python

import cgi
import cgitb

print "Content-type: text/html\n\n"

form=cgi.FieldStorage()

run_number = form.getvalue('run_number')
version = form.getvalue('ver')
period = form.getvalue('period')

openROOT_code="""
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
   <head>
      <title>Read a ROOT file</title>
      <meta http-equiv="X-UA-Compatible" content="IE=Edge; text/html">
      <script type="text/javascript" src="https://halldweb.jlab.org/data_monitoring/js/scripts/JSRootCore.js"></script>
   </head>
   <body onload="JSROOT.BuildSimpleGUI()">
"""

openROOT_code2=""
if version == "rawdata_ver00":
	openROOT_code2+=("<div id=\"simpleGUI\" files=\"https://halldweb.jlab.org/work/halld/online_monitoring/root/hdmon_online%06d.root\"> loading scripts... </div>" % (int(float(run_number))))
else:
	openROOT_code2+=("<div id=\"simpleGUI\" files=\"https://halldweb.jlab.org/work/halld/data_monitoring/%s/%s/rootfiles/hd_root_%06d.root\"> loading scripts... </div>" % (period, version, int(float(run_number))))

openROOT_code2+="</body> \n </html>"

print openROOT_code
print "test"
print openROOT_code2
