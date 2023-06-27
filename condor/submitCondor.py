import numpy as np 
import os
import glob
import argparse

eosPath = "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/input_files/condor_files/"
#files = [eosPath+"user.ebusch.364707.mc20e.v7p2_output.root/user.ebusch.33168179._000001.output.root", eosPath+"user.ebusch.364705.mc20a.v7p2_output.root/user.ebusch.33168149._000008.output.root"] 
#files = ["user.ebusch.33168149._000001.output.root","user.ebusch.33168164._000001.output.root"]
#-------------------------------------------------------------------------
if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    for file_list in ["test.txt"]:
        with open(file_list, "r") as f:
            files = []
            for line in f:
                line = line.strip()
                files.append(eosPath+line)

        for filePath in files:
            fileName = filePath.split("/")[-1] 
            # SUBMIT HERE
            print("SUBMITTING: input ", filePath)
            print("fileName", fileName)
            args = open("args.txt","write")
            os.system("echo '"+fileName+"' >>  args.txt")
            args.close()
            open("submit.sub","write")
 
            os.system("echo '#!/bin/bash' >> submit.sub")
            os.system("echo 'executable            = condor_run.sh' >> submit.sub") ##expand here to PC 
            #os.system("echo 'executable            = root -l 'fileSkimmer.C("+fileName+")'' >> submit.sub") ##expand here to PC 
            os.system("echo 'output                = logs.$(ClusterId).$(ProcId).out' >> submit.sub")
            os.system("echo 'error                 = logs.$(ClusterId).$(ProcId).err' >> submit.sub")
            os.system("echo 'log                   = logs.$(ClusterId).log' >> submit.sub")
            os.system("echo 'universe         = vanilla' >> submit.sub")
            os.system("echo 'getenv           = True' >> submit.sub")
            #os.system("echo 'Rank            = Mips' >> submit.sub")
            os.system("echo '+JobFlavour	= \"longlunch\"' >> submit.sub")
            os.system("echo '' >> submit.sub")
            os.system("echo 'should_transfer_files = YES' >> submit.sub")
            os.system("echo 'when_to_transfer_output = ON_EXIT' >> submit.sub")
            os.system("echo 'initialdir = /afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/condor/v8.1' >> submit.sub")
            os.system("echo 'workdir = /afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/condor' >> submit.sub")
            os.system("echo 'transfer_input_files = $(workdir)/condor_run.sh, $(workdir)/fileSkimmer.C, $(workdir)/fileSkimmer.h, "+filePath+"' >> submit.sub")
            os.system("echo 'transfer_output_files = skim0."+fileName+"' >> submit.sub")
            os.system("echo 'queue arguments from args.txt' >> submit.sub")
 
            os.system("condor_submit submit.sub")
            #time.sleep(.2)
            
            #open('submit.sub', 'w').close()
 
        print("DONE SUBMITTING... ")
