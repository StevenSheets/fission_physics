
import sys
import math
from ROOT import TH1F, TH2F, TFile
import numpy as np

# get the filename:
filename = sys.argv[1]
# get the type:
type = sys.argv[2]

if type=='mcnp':
	base = filename.strip(".txt")
else:
	base = filename.strip(".surf")

outfilename = base+'.root'
#outfile = open(outfilename,'w');

file = open(filename,'r')

Data = []
# time is in shakes (1e-8) in mcnp:
if type=='mcnp':
	lines = file.readlines()
	for line in lines[12:(len(lines)-1)]:
		hold = line.split();
		pid = math.floor( math.fabs(float(hold[1]))/1e6   )
		#convert shakes to nanoseconds:
		ltuple = (float(hold[4])*10, pid, float(hold[3]));
		Data.append(ltuple);

	SortedData = sorted( Data, key=lambda time: time[0]);

if type=='geant':
	for line in file:
		hold = line.split();
		pid=1
		if hold[2]=='neutron':
			pid=1
		if hold[2]=='gamma':
			pid=2
		#convert shakes to nanoseconds:
		ltuple = (float(hold[0]), pid, float(hold[1]));
		Data.append(ltuple);

	SortedData = sorted( Data, key=lambda time: time[0]);

	#for i in range( len( SortedData )):
	#	nt = SortedData[i];
	#	st = str(nt[0])+' '+str( nt[1])+' '+str(nt[2])+'\n';
	#	outfile.write(st);
	#outfile.close()

def genLogBins(nbins, axismin, axismax):
    factor = math.pow( axismax/axismin, 1./nbins)
    dbins = []
    dbins.append( axismin)
    for i in range(1, nbins+1):
        dbins.append( axismin*math.pow(factor, i))
    logbins = np.asarray(dbins)
    return logbins

firstEvent = 1
index = 0
previous_index = 0
previous_time = 0
nNeutrons = 0
nGammas = 0
gw = 500.0 # gatewidth, 500ns
multiG = np.zeros(100)
multiN = np.zeros(100)
hmulti = TH2F("Multi", "Multi", 30, -0.5, 29.5, 30, -0.5, 29.5);
def Multiplicity(time, pid):
	global previous_time
	global previous_index
	global nNeutrons, nGammas
	dt = time - previous_time
	index = math.floor( time/gw)
	if index==previous_index:
		if pid==1:
			nNeutrons+=1
		if pid==2:
			nGammas+=1
	# we passed the gate:
	if index!=previous_index:
		multiN[nNeutrons]+=1
		multiG[nGammas]+=1
		skipped_gates = index-previous_index
		multiN[0]+=skipped_gates
		multiG[0]+= skipped_gates
		hmulti.Fill(nNeutrons, nGammas)
		hmulti.SetBinContent(1,1,hmulti.GetBinContent(1,1)+skipped_gates)
		nNeutrons=0
		nGammas=0
		if pid==1:
			nNeutrons+=1
		if pid==2:
			nGammas+=1
	previous_time = time
	previous_index = index

print "Finished Sorting!\n"
hTI = TH1F("hTI", "hTI", 400, genLogBins(400, .1, 1e9))
hTIneutron = TH1F("hTIneutron", "hTIneutron", 400, genLogBins(400, .1, 1e9))
hTIgamma = TH1F("hTIgamma", "hTIgamma", 400, genLogBins(400, .1, 1e9))
hTIng = TH1F("hTIng", "hTIng", 400, genLogBins(400, .1, 1e9))
hEn = TH1F("hEn", "hEn", 1000, 0, 20)
hEg = TH1F("hEg", "hEg", 5000, 0, 20)
previous_time = 0.0
gprevious_time = 0.0
nprevious_time = 0.0

if type=='mcnp' or type=='geant':
	for item in SortedData:
		time = item[0]
		Energy = item[2]
		pid = item[1]
		Multiplicity(time, pid)
		if pid==1:
			hEn.Fill(Energy)
			hTIneutron.Fill( (time-nprevious_time))
			nprevious_time = time
			hTIng.Fill( (time - gprevious_time))
		if pid==2:
			hEg.Fill(Energy)
			hTIgamma.Fill( (time -gprevious_time))
			gprevious_time = time
		dt = time - previous_time

		hTI.Fill(dt)
		previous_time = time


Nscale = 1e5
f = TFile.Open(outfilename, 'recreate')
hTI.GetXaxis().SetTitle("time difference [ns]")
hTI.Write()
hmulti.SetOption("colz")
hmulti.GetXaxis().SetTitle("Neutron Multiplicity")
hmulti.GetYaxis().SetTitle("Gamma Multiplicity")
hmulti.Write()
hEn.GetXaxis().SetTitle("Neutron Energy [MeV]")
hEn.Write()
hEg.GetXaxis().SetTitle("Gamma Energy [MeV]")
hEg.Write()

hTIneutron.Write()
hTIgamma.Write()
hTIng.Write()
f.Close()
