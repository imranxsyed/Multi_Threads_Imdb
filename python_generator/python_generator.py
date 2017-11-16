
import io


dir = "1025//"
print "Executing ...."

for i in range(1,1026):

    #gettign the files
    source_file = open("source.csv", "r")
    file_name = str(i) + ".csv"
    dest_file = open ( dir + file_name, "w")

    #we read and write here
    lines = source_file.readlines()
    dest_file.writelines(lines)

    #close the files
    dest_file.close()
    source_file.close()


dir = "255//"

for i in range(1,256):

    #gettign the files
    source_file = open("source.csv", "r")
    file_name = str(i) + ".csv"
    dest_file = open ( dir + file_name, "w")

    #we read and write here
    lines = source_file.readlines()
    dest_file.writelines(lines)

    #close the files
    dest_file.close()
    source_file.close()



