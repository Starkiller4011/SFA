SFA - Structure Function Analysis

Version 0.9.9

Usage:

    sfa [options] path/to/input_file

Options:

    -o --output path/to/file
        Specifies the output file path. Does not need to already exist, sfa
        will create the file if it does not

    -d --delimiter "delimiter"
        Sets the delimiter to use when parsing the input file. Currently not
        implemented, WIP

    -v --verbose
        Set sfa to provide maximal output when running. Currently partially
        implemented, WIP
    
    input_file
        Mandatory argument, path to input_file must exist and input_file must
        contain only data in two columns, time and value collected at said time.
        WARNING: Current version only supports white-space delimited files and
        also requires any empty lines at the end of the file to be removed. WIP


Installation:

    There are two types of install for SFA, System-Wide and User-Specific.
    If you want to install SFA as a binary available to all users on the
    system then use the System-Wide method, this requires sudo priviledges
    however. If you do not have sudo rights and still need to use this program
    you can install using the User-Specific method. Using the User-Specific
    installation method creates the folder ~/.SFA and places the binary sfa
    inside, you will need to create and alias to this binary or append it
    to your PATH.

    1) Navigate to where you want to store the project files
        eg: cd ~/Downloads

    2) Clone the repository
        eg: git clone https://github.com/Starkiller4011/SFA.git

    3) Change directory to the project directory
        eg: cd SFA

    4) Install using the command for the type of install you want

        a) System-Wide (requires sudo priviledges)

            i) make install

        b) User-Specific (does not require sudo priviledges)

            i)  make user-install

            ii) Add the following alias to your ~/.bashrc or ~/.aliases file
            
                alias sfa="~/.SFA/sfa"
            
            iii) Or append ~/.SFA to your PATH
        
    5) Optional: Delete the project folder
        eg: cd ..
            rm -R SFA

Uninstallation:

    If you wish to uninstall SFA or want to upgrade it to a newer version, you
    will require the projecct folder. The following directions assume the SFA
    project folder was deleted Post-Installation.

    1) Download the project folder and files
        eg: git clone https://github.com/Starkiller4011/SFA.git
    
    2) Change directory to the project directory
        eg: cd SFA

    3) Uninstall using the command for the type of install you have

        a) System-Wide
            eg: make uninstall

        b) User-Specific
            eg: make user-uninstall
    
    4) Optional: Delete the project folder
        eg: cd ..
            rm -R SFA


If using this software for publication purposes please cite Gallo, L. C., Blue, D. M., Grupe, D., Komossa, S., & Wilkins, D. R. 2018, MNRAS , 478,2557
Nasa ADS: https://ui.adsabs.harvard.edu/abs/2018MNRAS.478.2557G/abstract

arxiv: https://arxiv.org/abs/1805.00300

Copyright © Derek Blue 2019
This software is distributed under a provisional MIT License. See the LICENSE file
for more details.
