# KPDGUI: Visualization Software for Kidney Paired-Donation

### Software Description

The aim in kidney paired-donation (KPD) is typically to maximize the utility achieved via cycles among incompatible donor-candidate pairs, as well as chains originating from non-directed donors (NDD). With many possible overlapping options in a KPD pool, a preferable choice of cycles and chains realistically cannot be found by simple inspection. In practice, objective criteria are used to define near-optimal solutions, but with the increasing complexity of the criteria used, solutions can be difficult to compare or visualize. 

We present a software platform for managing and visualizing exchanges suggested by optimization criteria in KPD, which offers several advantages over other available software:  

1. An interactive visual display of the state of the KPD, including active and inactive pairs/NDDs, as well as donor & candidate characteristics.
2. Implementation of optimization methods from previous literature that account for probabilities of failure between selection and transplantation, for each pair and match, as well as fallback options (sub-cycles and sub-chains) for immediate recourse in the case of such failures. 
3. Optimization is extended beyond the selection of simple cycles or chains, to more general subsets of pairs and NDDs that facilitate fallback options.


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

* Interactive visual display of the pairs/NDDs and matches in the KPD pool, as well as selectable and sortable lists of the pairs/NDDs 
  + Pairs/NDDs can be selected, moved, deleted in the visualization 
  + Additionally, groups of pairs/NDDs can be selected, clustered 
* Ability to input individual pairs/NDDs, or upload a structured data file of several pairs/NDDs 
* Estimation of graft survival probabilities based on donor and candidate characteristics for each match 
* Various user options for running optimizations
  + Constraints on the sizes of cycles and chains
  + Failure probabilities (on pairs/NDDs as well as matches)
  + Choice of utility function; either number of transplants or total estimated 5- or 10-year graft survival 
  + Certain administrative policies, such as priority for highly sensitized candidates or reserving O donors for O candidates
* Shading indicates degree of sensitization, i.e. panel reactive antibody (PRA)
* KPD pools can be saved (encrypted) in their current state
  + Loading a saved KPD pool will restore all previously found solutions
* Subsets of pairs can be hidden in the visualization, e.g. if they are to be left out of selection, or have no compatibilities
* Pairs can be sorted by ID, appearances in cycles/chains or solutions, number of compatibilities, compatible donors or compatible recipients, or by PRA; matches can be sorted by donor or candidate ID, or by appearances in cycles/chains or solutions
* Matches are automatically determined based on pair information whenever a pair or NDD is added 
* By default, matches between pairs are only shown when both pairs are selected; match display options include showing selected compatible recipients, compatible donors, or all or no compatibilities


### More Information

Software was developed in C++, using [Gurobi](www.gurobi.com) for optimization, and [Qt](www.qt.io) for the graphical user interface. All materials associated with this project can be accessed at our [website](http://www.kecc.sph.umich.edu/projects/optimization-and-simulation-kidney-paired-donation-program). **This project is open-source under the terms of the (GNU) LPGL license.**


### Disclaimer

**LIMITATIONS OF LIABILITY:** When you access this software, you agree that the authors and the University of Michigan will not be liable to you for any loss or injury caused in procuring, compiling, or delivering the information gained from the software. In no event will the authors or the University of Michigan be liable to you or anyone else for any action taken by you on the basis of such information or for any incidental, consequential, special, or similar damages.

**NOT MEDICAL ADVICE:** The content contained in this software is not intended to and does not constitute medical advice. The accuracy, completeness, adequacy, or currency of the content is not warranted or guaranteed. The use of information from this software is at the user's own risk. Users should never disregard professional medical advice or delay in seeking it because of something resulting from the software.

Mathieu Bray 2016. *KPDGUI: A Visualization Software Platform for Managing a Kidney Paired-Donation Program.* Contributions: M. Bray, W. Wang, M.A. Rees, P.X-K. Song, A.B. Leichtman, V.B. Ashby, J.D. Kalbfleisch. This work was supported in part by the National Institute of Diabetes and Digestive and Kidney Diseases (NIDDK) through grant number 1R01-DK093513. Dr. Rees  is supported in part by NIAID grants R21 AI-111579 and R01-AI090244. Drs. Rees and Leichtman are supported in part by AHRQ grant R18 HS-020610. The authors have no relevant financial relationships with commercial interests to disclose.

