#! /usr/bin/python
cPath = "./"

import os

def Compact (cFile):
    cTmpFile = cFile + "tmp"
    fIn = open(cFile, "rt")
    fOut = open(cTmpFile, "wt")

    iNum = 0
    cRepStr = ""

    for cLine in fIn:
        if iNum != 0:
            if cLine == cRepStr:
                iNum = iNum + 1
            else:
                if iNum == 1:
                    fOut.write(cRepStr)
                elif iNum == 2:
                    fOut.write(cRepStr)
                    fOut.write(cRepStr)
                else:
                    fOut.write(".rept " + str(iNum) + "\n" + cRepStr +  ".endr\n")
                iNum = 0
                #cRepStr = ""

        if iNum == 0:
            if cLine.startswith(".byte "):
                iNum = 1
                cRepStr = cLine
            else:
                fOut.write(cLine)

    if iNum != 0:
        if iNum == 1:
            fOut.write(cRepStr)
        elif iNum == 2:
            fOut.write(cRepStr)
            fOut.write(cRepStr)
        else:
            fOut.write(".rept " + str(iNum) + "\n" + cRepStr +  ".endr\n")

    fOut.close()
    fIn.close()

    os.remove(cFile)
    os.rename(cTmpFile, cFile)

os.rename(cPath + "war-asm.asm", cPath + "war-asm.s")
Compact(cPath + "seg01.inc")
Compact(cPath + "seg02.inc")