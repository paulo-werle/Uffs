import matplotlib.pyplot as plt
from tabulate import tabulate
import numpy as np

class Bisection:
  ##### Entradas #####
  def __init__(self):
    self.inA     = -2
    self.inB     = 2
    self.epsilon = 0.00005
    self.outputs = []

  def function(self, x):
    return pow(x, 3) - 2

  ##### Processamento #####
  def method(self):
    return (self.inA + self.inB) / 2

  def comparation(self):
    return (self.inB - self.inA) <= self.epsilon

  def includeOutput(self, iteration, value):
    self.outputs.append([ iteration, self.inA, self.inB, value, self.function(value) ])

  def bisection(self):
    if self.comparation(): return
    value = self.function(self.inA)
    iterations = 0

    while True:
      x = self.method()
      if value * self.function(x) > 0:
        self.inA = x
      else:
        self.inB = x

      self.includeOutput(iterations, x)
      iterations += 1
      if self.comparation(): return

  ##### Saida #####
  def printValues(self):
    print(tabulate(self.outputs, headers=['Iteração', 'A', 'B', 'X', 'f(x)']))

  def generateGraph(self):
    xMin = 0
    xMax = 2
    linspace = np.linspace(xMin, xMax, 100)

    plt.figure(dpi = 100, figsize = (5, 5))
    plt.suptitle("Metodo da Bisseção")
    plt.hlines(y = 0, xmin = xMin, xmax = xMax)
    plt.plot(linspace, self.function(linspace), color = 'blue')
    for output in self.outputs:
      plt.plot(output[3], 0, marker = 'o', color= 'red')
    plt.show()

##### Execução #####
instance = Bisection()
instance.bisection()
instance.printValues()
instance.generateGraph()
