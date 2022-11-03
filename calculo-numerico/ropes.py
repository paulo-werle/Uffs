import matplotlib.pyplot as plt
from tabulate import tabulate
import numpy as np

class Ropes:
  ##### Entradas #####
  def __init__(self):
    self.inA     = -2
    self.inB     = 2
    self.epsilon = 0.00005
    self.outputs = []

    self.xMin = self.inA
    self.xMax = self.inB

  def inA():
    return float(self.inA)

  def inB():
    return float(self.inB)

  def function(self, x):
    return pow(x, 3) - 2

  ##### Processamento #####
  def method(self):
    funcA = self.function(self.inA)
    funcB = self.function(self.inB)

    auxValue = (funcB - funcA) / (self.inB - self.inA)
    value    = self.inB - funcB / auxValue
    return value

  def comparation(self):
    return abs((self.inB - self.inA) / self.inB) <= self.epsilon

  def includeOutput(self, iteration, value):
    self.outputs.append([ iteration, self.inA, self.inB, value, self.function(value) ])

  def ropes(self):
    if self.comparation(): return
    iterations = 0

    while True:
      value = self.method()
      self.inA = self.inB
      self.inB = value

      self.includeOutput(iterations, value)
      iterations += 1
      if self.comparation(): return

  ##### Saida #####
  def printValues(self):
    print(tabulate(self.outputs, headers=['Iteração', 'A', 'B', 'X', 'f(x)']))

  def generateGraph(self):
    linspace = np.linspace(self.xMin, self.xMax, 100)

    plt.figure(dpi = 100, figsize = (5, 5))
    plt.suptitle("Metodo das Cordas")
    plt.hlines(y = 0, xmin = self.xMin, xmax = self.xMax)
    plt.plot(linspace, self.function(linspace), color = 'blue')
    for output in self.outputs:
      plt.plot(output[3], 0, marker = 'o', color= 'red')
    plt.show()

##### Execução #####
instance = Ropes()
instance.ropes()
instance.printValues()
instance.generateGraph()
