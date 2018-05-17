## Ideas:
##   + read in a CSV file. For each line, split the line on ','
##     and process the fields. 
## 
##     Country (code), Mapped IP Addresses, Daily Traffic (MB)
##     Italy (IT), 12345, 432562 MB
##
##     Output:
##     Code, Traffic per IP
##     Code, 0.0285 MB/IP
##
## Filter Banned countries as well (based on code)

f = read_file('data.txt')
out = []
f.lines.each do |line|
    out << line.chomp.gsub(/^\+/, "\t+")
end