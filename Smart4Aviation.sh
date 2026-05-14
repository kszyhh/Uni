#!/bin/bash

# The script renames log files with the current date, compresses them, 
# and removes archives older than 10 days.

mapfile -t path_of_logs < <(find /opt/logs -type f -name "*.log.*" 2>/dev/null)  #reading paths into array

date_formatted=$(date +%F) 

if [[ "${#path_of_logs[@]}" -eq 0 ]]
then
    echo "No .log. files found"
    exit 0 
fi

for i in "${path_of_logs[@]}"
    do
        
        base_name="$(basename "$i")" #only name of the file 
        dir_name="$(dirname "$i")" #only path of the file 

        name="${base_name%%.log.*}" #everything before .log.
        rest="${base_name##*.log.}" #everything after .log.
        
        mv "$i" "$dir_name/$name.$date_formatted.log.$rest"  
        gzip "$dir_name/$name.$date_formatted.log.$rest" #with -k logs would be kept 
        
done
find /opt/logs -type f -name "*.log.*.gz" -mtime +10 -delete