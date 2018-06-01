# KPDGUI: Visualization Software for Kidney Paired-Donation

### Software Description

The aim in kidney paired-donation is typically to maximize the number of transplants achieved through the exchange of donors in a pool comprising incompatible donor-candidate pairs, along with non-directed (or altruistic) donors. With many possible allocations at any given time, an optimal set of exchanges cannot be determined by simple inspection. In practice, objective criteria are used to determine an optimal or near-optimal set of exchanges to pursue.  

We present a software application for management and optimization of a kidney paired donation program, KPDGUI (Kidney Paired Donation Graphical User Interface). We implement a variety of published optimization schemes, while offering the user an interactive and visual environment. The application allows comparison of exchanges suggested under different optimization criteria, and examination of the consequences of various policies on proposed solutions. 

KPDGUI offers the following advantages over the most common alternatives:

1. An interactive visual display of the current state of the KPD program.
2. Implementation of optimization methods from previous literature[5,6], which can be used to account for (a) probabilities that preferred transplants are unviable either due to positive crossmatch or through the unavailability of a candidate or donor in the exchange, and (b) fallback options for immediate recourse in case potential exchanges are unable to proceed as determined due to unviability.
3. Optimization is extended beyond selection of simple cycles or chains to more general subsets of pairs, possibly with more than one associated incompatible donor, and NDDs that facilitate fallback options in the case of unviability[7].



### Instructions for Download

1. Download this package as a .zip (click the green 'Clone or Download' button at the top right)
2. Visit the [Gurobi](www.gurobi.com) website, set up an account and download a free installation of the Gurobi Optimizer.
  + You will need to download a license in order for the software to run Gurobi. Free academic licenses are available for use by faculty members, students, or members of the research or administrative staffs of degree-granting academic institutions (you will need to be logged in to the network of such an institution to obtaine the free license).
  + When installing your license, save the license file in the default location.
3. Navigate to the 'x64/Release/' folder.
4. Run KPDGUI.exe
  + If optimization does not work when running the software, it may be that the license file cannot be found. If this is the case, set an environment variable 'GRB_LICENSE_FILE' to point to the exact location of the license file.

Synthetic examples, both in .kpd and .csv format, can be found in the 'examples' folder. Tutorial videos for how to use the software can be found in the 'tutorials' folder. Alternatively, the tutorial videos are available on the author's channel on [YouTube](https://www.youtube.com/channel/UCUy5Z6IUDXUZ8MPRLPTJntw)


### Features

* Interactive visual display of pairs, NDDs and matches in the KPD pool, as well as sortable lists of pairs, donors, candidates, matches, and found transplant arrangements and solutions.
* Ability to add individual pairs and NDDs, or upload a structured dataset with information on an existing KPD pool. 
* Matches automatically determined based on virtual crossmatch results with all pairs in the pool whenever a pair or NDD is added. 
* Various user options for running optimizations:
  + Constraints on the sizes of cycles, chains, and LRSs
  + Choice of utility to assign to each match (e.g. number of transplants, estimated 5- or 10-year graft survival, etc.) 
  + Other administrative policies (e.g. priority for highly sensitized candidates, reserving O donors for O candidates, etc.)
* Ability to edit individual characteristics by right-clicking donors, candidates, or matches.
* KPD program can be saved in current state to be loaded at later time.


### More Information

Software was developed in C++, using [Gurobi](www.gurobi.com) for optimization, and [Qt](www.qt.io) for the graphical user interface. All materials associated with this project can be accessed at our [website](http://www.kecc.sph.umich.edu/projects/optimization-and-simulation-kidney-paired-donation-program). **This project is open-source under the terms of the (GNU) LPGL license.**


### Disclaimer

**LIMITATIONS OF LIABILITY:** When you access this software, you agree that the authors and the University of Michigan will not be liable to you for any loss or injury caused in procuring, compiling, or delivering the information gained from the software. In no event will the authors or the University of Michigan be liable to you or anyone else for any action taken by you on the basis of such information or for any incidental, consequential, special, or similar damages.

**NOT MEDICAL ADVICE:** The content contained in this software is not intended to and does not constitute medical advice. The accuracy, completeness, adequacy, or currency of the content is not warranted or guaranteed. The use of information from this software is at the user's own risk. Users should never disregard professional medical advice or delay in seeking it because of something resulting from the software.

Mathieu Bray 2016-2018. *KPDGUI: Interactive Software for Management of a Kidney Paired-Donation Program.* Contributions: M. Bray, W. Wang, M.A. Rees, P.X-K. Song, A.B. Leichtman, V.B. Ashby, J.D. Kalbfleisch. This work was supported in part by the National Institute of Diabetes and Digestive and Kidney Diseases (NIDDK) through grant number 1R01-DK093513. Dr. Rees  is supported in part by NIAID grants R21 AI-111579 and R01-AI090244. Drs. Rees and Leichtman are supported in part by AHRQ grant R18 HS-020610. The authors have no relevant financial relationships with commercial interests to disclose.

