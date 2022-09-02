
The code is split into 4 files:
  - project_Pv~.C
        -> This is the processing code which runs through an event loop of all the v1 ntuple signal points (refered to as samples within the code) and then writes filled                  histograms and vectors for later drawing / event displays.
        -> It is split into 4 main sections; booking the histograms, the event loop, filling the histograms & writing the histograms.
        -> There are also portions of the code dedicated to printing some tables in relation to certain defined criteria pre & post cuts.
        -> There is an option to change to truth jets at initial defiiton section of the code but there is an issue with the values of the truth 
           jets properties at the moment.
        
  - project_Mv~.C
        -> This is the plotting code which reads the files created from project_Pv~.C and draws the histograms selected within the code with variable bin sizes.
        -> All you need to do to choose the histograms to draw is add their names from project_P code, their desired number of bins and their xaxis label to a set of lists.
        -> All hists are seved with 5040 (7!) bins so any rebinning number which divides this is acceptable. 
        -> Additionally there are options for choosing to draw the 1D hist and/or the 2D hists and also normalise the 1D hists below the set of lists. 
        
  - project_EDv~.C
         -> This is the Event Display code which take saved vectors from the project_P files and draws the specified events in the display format and saves them to pdf files               after darwing.
  
  - project_Hv~.h
         -> This is a very basic header file which contains constants which need to be shared between the project_P, project_M and project_ED files.
         
The way to us the files is to run project_Pv~.C first and then run either project_Mv~.C or project_EDv~.C depending on what you want done.
