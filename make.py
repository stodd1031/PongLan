import os
import subprocess

PROJECT_NAME = "pongLan"

SOURCE_DIR="src/"
BUILD_DIR="build/"
INCLUDE_DIR=""
HEADER_DIR="src/"
EXE_DIR=""

LIBRARIES = "-pthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system"

#------------------------

SOURCES = []

# os.system("ls " + SOURCE_DIR + " | grep .cpp")
SOURCE_DIR_FILES = os.listdir(SOURCE_DIR)
SOURCES = []
for file in SOURCE_DIR_FILES:
    if ".cpp" in file:
        SOURCES.append(file)
SOURCE_WDIR = ["src/" + s for s in SOURCES]

HEADER_DIR_FILES = os.listdir(HEADER_DIR)
HEADERS = []
for file in SOURCE_DIR_FILES:
    if ".h" in file or ".hpp" in file:
        HEADERS.append(file)

OBJECTS = []

for source in SOURCES:
    OBJECTS.append(source[0:-4] + ".o")

OBJECTS_WLOCATION = []
for object in OBJECTS:
    OBJECTS_WLOCATION.append(BUILD_DIR + object)

CHANGED = []
for index in range(0, len(SOURCES)):
    if os.path.getmtime(SOURCE_DIR + SOURCES[index]) > os.path.getmtime(BUILD_DIR + OBJECTS[index]):
        CHANGED.append(SOURCE_DIR + SOURCES[index])

for index in range(0, len(HEADERS)):
    if ".hpp" in HEADERS[index]:
        if HEADERS[index][0:-4] + ".cpp" in SOURCES:
            HEADER_WLOCATION = HEADER_DIR + HEADERS[index]
            HEADER_TO_OJECT_WLOCATION = BUILD_DIR + HEADERS[index][0:-4] + ".o"
            if os.path.getmtime(HEADER_WLOCATION) > os.path.getmtime(HEADER_TO_OJECT_WLOCATION):
                HEADER_TO_SORUICE_WDIR = SOURCE_DIR + HEADERS[index][0:-4]+ ".cpp"
                if HEADER_TO_SORUICE_WDIR not in CHANGED:
                    CHANGED.append(HEADER_TO_SORUICE_WDIR)
    elif ".h" in HEADERS[index]:
        if HEADERS[index][0:-2] + ".cpp" in SOURCES:
            HEADER_WLOCATION = HEADER_DIR + HEADERS[index]
            HEADER_TO_OJECT_WLOCATION = BUILD_DIR + HEADERS[index][0:-2] + ".o"
            if os.path.getmtime(HEADER_WLOCATION) > os.path.getmtime(HEADER_TO_OJECT_WLOCATION):
                HEADER_TO_SORUICE_WDIR = SOURCE_DIR + HEADERS[index][0:-2]+ ".cpp"
                if HEADER_TO_SORUICE_WDIR not in CHANGED:
                    CHANGED.append(HEADER_TO_SORUICE_WDIR)


def getDepend(file):
    array = []
    dep = str(subprocess.check_output(["g++", "-MM", file]))
    for index in range(0, len(dep)):
        if dep[index] == '.' and dep[index+1] == 'h':
            string = ""
            for indexBak in range(index, 0, -1):
                if dep[indexBak] == ' ': 
                    string = string + "cpp"
                    if file != string and string in SOURCE_WDIR:
                        array.append(string)
                    break
                string = dep[indexBak] + string
    return array

# print(getDepend("src/main.cpp"))
                
COMPILED = []

def sourceWLocToObjectWLoc(source):
    buildDestWCPP = source.replace(SOURCE_DIR, BUILD_DIR)
    return buildDestWCPP.replace(".cpp", ".o")

def comp(files):
    returnBool = False
    for file in files:
        if len(COMPILED) == len(CHANGED):
            break
        lowerCompiled = False
        if(getDepend(file) != []):
            lowerCompiled = comp(getDepend(file))
        if(file in CHANGED) and (file not in COMPILED):
            print("compiled " + file)
            os.system("g++" + " -c " + file + " -o " + sourceWLocToObjectWLoc(file))
            COMPILED.append(file)
        if lowerCompiled and (file not in COMPILED):
            print("compiled " +file)
            os.system("g++" + " -c " + file + " -o " + sourceWLocToObjectWLoc(file))
            COMPILED.append(file)
        
        if file in COMPILED:
            returnBool = True
    return returnBool

comp(SOURCE_WDIR)

# print(CHANGED)
if CHANGED != []:
    print("compiled " + PROJECT_NAME)
    os.system("g++ " + ' '.join(OBJECTS_WLOCATION) + " -o " + PROJECT_NAME + " " + LIBRARIES)