from ast import Str
import pygame;
from sys import exit
import random

pygame.init()
clock = pygame.time.Clock()
getTicksLastFrame = 0

class Window:
    def __init__(self,width:float,height:float,title:Str):
        self.screen = pygame.display.set_mode((width,height))
        pygame.display.set_caption(title)
        self.width = width
        self.height = height

window = Window(509,339,'Asteroid')

class Point2f:
    def __init__(self,x:float,y:float):
        self.x = x
        self.y = y

class Vector2f:
    def __init__(self,x:float,y:float):
        self.x = x
        self.y = y
    def __str__(self):
        return f"({self.x}, {self.y})"
    def __repr__(self):
        return f"({self.x}, {self.y})"
    def __gt__(self,other):
        if self.x == other.x:
            return self.y > other.y
        return self.x > other.x
    def __lt__(self,other):
        if self.x == other.x:
            return self.y < other.y
        return self.x < other.x
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    def dot(self,other):
        return self.x * other.x + self.y * other.y
    def cross(self,other):
        return self.x * other.y- other.x * self.y
    def __add__(self,other):
        return Vector2f(self.x+other.x,self.y+other.y)

class Rectf:
    def __init__(self,bottomLeft:Point2f,width:float,height:float):
        self.left = bottomLeft.x
        self.bottom = bottomLeft.y
        self.shape = pygame.Surface((width,height))
    def draw(self):
        window.screen.blit(self.shape,(self.left,self.bottom))
    def setColor(self,color):
        self.shape.fill(color)

class Texture:
    def __init__(self,path:Str):
        self.texture = pygame.image.load(path)
    def draw(self,position:Point2f):
        window.screen.blit(self.texture,(position.x,position.y))
    def getWidth(self):
        return self.texture.get_width()
    def getHeight(self):
        return self.texture.get_height()

class Text:
    def __init__(self,path:Str,text:Str,size:int,color):
        self.font = pygame.font.Font(path,size)
        self.render = self.font.render(text,False,color)
    def draw(self,position:Point2f):
        window.screen.blit(self.render,(position.x,position.y))

background = Texture('Resources/background.jpg')
font = Text('Resources/DIN-Light.otf','Asteroid',50,'Green')

class asteroid:
    def __init__(self,position:Point2f):
        self.position = position
        self.texture = Texture('Resources/Asteroid.png')
        self.vector = Vector2f(random.randint(100,150),random.randint(100,150))
    def draw(self):
        self.texture.draw(self.position)
    def update(self,elapsedSec:float):
        self.position.x += self.vector.x * elapsedSec;
        self.position.y += self.vector.y * elapsedSec;
        if self.position.x+self.texture.getWidth()/2.0 > window.width or self.position.x+self.texture.getWidth()/2 < 0:
            if self.vector.x < 0:
                self.position.x += 1
            else:
                self.position.x -= 1
            self.vector.x = -self.vector.x
        if self.position.y+self.texture.getHeight()/2.0 > window.height or self.position.y+self.texture.getHeight()/2 < 0:
            if self.vector.y < 0:
                self.position.y += 1
            else:
                self.position.y -= 1
            self.vector.y = -self.vector.y

a = [asteroid(Point2f(50,50))]
counter = 0
while counter < 5:
    x = random.randint(0,window.width)
    y = random.randint(0,window.height)
    a.insert(len(a),asteroid(Point2f(x,y)))
    counter+=1

def draw():
    background.draw(Point2f(0,0))
    font.draw(Point2f(50,50))
    for i in a:
        i.draw()

def update(elapsedSec:float):
    for i in a:
        i.update(elapsedSec)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
            
    draw()
    t = pygame.time.get_ticks()
    deltaTime = (t - getTicksLastFrame) / 1000.0
    getTicksLastFrame = t
    update(deltaTime)

    pygame.display.update()
    clock.tick(60)