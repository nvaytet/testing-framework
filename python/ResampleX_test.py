from mantid.simpleapi import *

wksp='wksp'
binning = "0.05,16000,3.5"
lambdaMin, lambdaBinning, lambdaMax = [ float(x) for x in binning.split(',') ]
lambdaDelta = (lambdaMax - lambdaMin) / lambdaBinning
print(lambdaMin, lambdaDelta, lambdaMax)

CreateSampleWorkspace(OutputWorkspace=wksp,
                      Xmin=lambdaMin,
                      Xmax=lambdaMax,
                      BinWidth=lambdaDelta,
                      XUnit='Wavelength')

ResampleX(InputWorkspace=wksp,
          OutputWorkspace=wksp+'1',
          XMin=[lambdaMin],
          XMax=[lambdaMax],
          NumberBins=int(lambdaBinning))

print("-"*35)
print("Workspace2D: Distribution == False => Success!")
print("-"*35)

ConvertToDistribution(wksp)

ResampleX(InputWorkspace=wksp,
          OutputWorkspace=wksp+'2',
          XMin=[lambdaMin],
          XMax=[lambdaMax],
          NumberBins=int(lambdaBinning))

print("-"*35)
print("Workspace2D: Distribution == True => Success!")
print("-"*35)

