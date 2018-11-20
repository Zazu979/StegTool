#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Author: zazu
# @Date:   2018-11-19 20:28:20
# @Last Modified by:   zazu
# @Last Modified time: 2018-11-20 11:46:51

import sys
import cv2
import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--image", help="The image file that is to be used",action="store_true")
parser.add_argument("-t", "--textfile", help="The text file to be hidden",action="store_true")
parser.add_argument("-o", "--output", help="The output file that is to be used",action="store_true")
parser.add_argument("-d", "--desteg", help="Undo the steganography on an image",action="store_true")
parser.add_argument("-e", "--encrypt", help="Enable encyption. Password to be prompted",action="store_true")
args = parser.parse_args()

def convertValue(value, bit):
   # Edge case when value is max value
   if value == 255 and bit == 0:
      return 254

   # Return off when bit = 1 and even when bit  = 0
   return value if value % 2 == bit else value + 1


def fileToBinary(filename):

   print("Reading Textfile")
   try:
      file = open(filename)

      text = file.read()
      contents  = ''.join(format(ord(x), 'b') for x in text)
      contents += '0000000'

      file.close()
   except IOError as e:
      print("Error with input file")
      raise

   return contents
   
def createSteg(image, text):
   print("Opening image")
   contents = cv2.imread(image, cv2.IMREAD_COLOR)
   rows = contents.shape[0]
   cols = contents.shape[1]

   maxLength = rows * cols * 3

   # Iterate through the text
   ii = 0
   length = len(text)

   if length > maxLength:
      print("Image is not large enough to hold this file.")
      raise

   print(text)
      
   print("Starting steganography")
   for x in range(0, rows):
      for y in range(0, cols):
         pixel = contents[x,y]
         for z in range(0,3):
            if ii < length:
               pixel[z] = convertValue(pixel[z], int(text[ii]))
               ii = ii + 1
            else:
               # else do nothing. Youre done
               return contents

   return contents

def stegToText(value):
   return value % 2 

def readSteg(filename):
   print("Opening image")
   contents = cv2.imread(filename, cv2.IMREAD_COLOR)
   rows = contents.shape[0]
   cols = contents.shape[1]

   ii = 0

   binaryValue = ""

   text = ""

   print("Starting Steg reversion")
   for x in range(0, rows):
      for y in range(0, cols):
         pixel = contents[x,y]
         for z in range(0,3):
            singleValue = pixel[z]

            binaryValue = binaryValue + str(singleValue % 2)

            if(ii == 6):

               # Youve hit the null terminator and youre all done
               if(binaryValue == "0000000"):
                  return text

               singleValue = chr(int(binaryValue, 2))
               text = text + singleValue

               # Reset values
               ii = 0
               binaryValue = ""
            else:
               ii = ii + 1 

   raise
            

def saveImage(filename, pixels):
   print("Saving image")
   cv2.imwrite(filename, pixels)

def saveText(filename, text):
   print("Saving textfile")
   file = open(filename, "w")
   file.write(text)
   file.close()

def main(command, imageFile, textFile):

   if command == "-e":
      try:
         text = fileToBinary(textFile)
         newImage = createSteg(imageFile, text)
         saveImage("filename", newImage)
      except Exception as e:
         pass
   elif command == "-d":
      try:
         text = readSteg(imageFile)
         saveText(textFile, text)
      except:
         raise
   else:
      help()

def help():
   print(parser.parse_args)

if __name__ == "__main__":

   argc = len(sys.argv)
   if argc >= 4:
      main(sys.argv[1],sys.argv[2],sys.argv[3])
   else:
      help()
      
