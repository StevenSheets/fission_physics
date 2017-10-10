
from ROOT import TFile, TH1F, TH2F,TLegend,TCanvas

# raw counts (n/g):
# mcnp: 210905/36069
# g4fisslib: 208155/48602
# qgsp_bic_hp: 208900/24448 

f1 = TFile.Open("duball.in.root")
f2 = TFile.Open("myphysic.root")
f3 = TFile.Open("qgsp_bic_hp.root")
N = 1e5
hEg1 = f1.Get("hEg")
hEg2 = f2.Get("hEg")
hEg3 = f3.Get("hEg")

hEg1.Scale(1/N)
hEg1.Rebin(2)
hEg2.Scale(1/N)
hEg2.Rebin(2)
hEg3.Scale(1/N)
hEg3.Rebin(2)

hEg1.GetXaxis().SetRangeUser(0,10)
hEg1.GetYaxis().SetTitle("Particles per incident neutron")
hEg1.Draw()
hEg2.SetLineColor(2)
hEg2.Draw("Csame")
hEg3.SetLineColor(3)
hEg3.Draw("Csame")

leg = TLegend(.6,.6,.7,.8)
leg.AddEntry(hEg1, "MCNPXv270");
leg.AddEntry(hEg2, "G4FissLib");
leg.AddEntry(hEg3, "QGSP_BIC_HP")
leg.Draw()

hEn1 = f1.Get("hEn")
hEn2 = f2.Get("hEn")
hEn3 = f3.Get("hEn")

hEn1.Scale(1/N)
hEn1.Rebin(2)
hEn2.Scale(1/N)
hEn2.Rebin(2)
hEn3.Scale(1/N)
hEn3.Rebin(2)

c2 = TCanvas()

hEn1.GetXaxis().SetRangeUser(0,20)
hEn1.GetYaxis().SetTitle("Particles per incident neutron")
hEn1.Draw()
hEn2.SetLineColor(2)
hEn2.Draw("Csame")
hEn3.SetLineColor(3)
hEn3.Draw("Csame")
leg.Draw()

hm1 = f1.Get("Multi")
hm2 = f2.Get("Multi")
hm3 = f3.Get("Multi")

c3 = TCanvas()
c3.Divide(3,1)
c3.cd(1)
hm1.SetTitle("MCNPX")
hm1.Draw()
c3.cd(2)
hm2.SetTitle("G4FissLib")
hm2.Draw()
c3.cd(3)
hm3.SetTitle("QGSP_BIC_HP")
hm3.Draw()


