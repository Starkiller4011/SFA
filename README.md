SFA - Structure Function Analysis

Version 0.6.4

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
        WARNING: Current version only supports white-space delimited
        files and also requires any empty lines at the end of the file to be
        removed. WIP