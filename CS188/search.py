# search.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
In search.py, you will implement generic search algorithms which are called
by Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
  """
  This class outlines the structure of a search problem, but doesn't implement
  any of the methods (in object-oriented terminology: an abstract class).

  You do not need to change anything in this class, ever.
  """

  def getStartState(self):
     """
     Returns the start state for the search problem
     """
     util.raiseNotDefined()

  def isGoalState(self, state):
     """
       state: Search state

     Returns True if and only if the state is a valid goal state
     """
     util.raiseNotDefined()

  def getSuccessors(self, state):
     """
       state: Search state

     For a given state, this should return a list of triples,
     (successor, action, stepCost), where 'successor' is a
     successor to the current state, 'action' is the action
     required to get there, and 'stepCost' is the incremental
     cost of expanding to that successor
     """
     util.raiseNotDefined()

  def getCostOfActions(self, actions):
     """
      actions: A list of actions to take

     This method returns the total cost of a particular sequence of actions.  The sequence must
     be composed of legal moves
     """
     util.raiseNotDefined()


def tinyMazeSearch(problem):
  """
  Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze
  """
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s,s,w,s,w,w,s,w]

def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first [p 85].

  Your search algorithm needs to return a list of actions that reaches
  the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].

  To get started, you might want to try some of these simple commands to
  understand the search problem that is being passed in:

  print "Start:", problem.getStartState()
  print "Is the start a goal?", problem.isGoalState(problem.getStartState())
  print "Start's successors:", problem.getSuccessors(problem.getStartState())
  """
  "*** YOUR CODE HERE ***"
  from util import Stack

  q = Stack()
  q.push((problem.getStartState(),[]))

  used = {}

  while not q.isEmpty():
      curr = q.pop()

      if curr[0] in used:
          continue
      used[curr[0]] = 1

      if problem.isGoalState(curr[0]) is True:
          return curr[1]

      for nxt in problem.getSuccessors(curr[0]):
          q.push((nxt[0],curr[1]+[nxt[1]]))


  util.raiseNotDefined()

def breadthFirstSearch(problem):
  "Search the shallowest nodes in the search tree first. [p 81]"
  "*** YOUR CODE HERE ***"

  from util import Queue
  from itertools import permutations


  try:
      ans = []
      corners = problem.getCorners()

      for permutation in permutations(corners):
          q = Queue()
          q.push((problem.getStartState(),[]))

          used = {}

          goal = permutation[0]

          while not q.isEmpty():

              curr = q.pop()

              if curr[0] == goal:
                  used.clear()
                  permutation = [i for i in permutation if i!=permutation[0]]
                  while not q.isEmpty():
                      q.pop()
                  q.push(curr)
                  if len(permutation) == 0:
                      if len(ans) == 0 or len(curr[1])<len(ans):
                          ans = curr[1]
                      break
                  goal = permutation[0]

              if curr[0] in used:
                  continue
              used[curr[0]] = 1

              for nxt in problem.getSuccessors(curr[0]):
                  q.push((nxt[0],curr[1]+[nxt[1]]))

      return ans


  except:
      q = Queue()
      q.push((problem.getStartState(),[]))

      used = {}

      while not q.isEmpty():
          curr = q.pop()

          if curr[0] in used:
              continue
          used[curr[0]] = 1

          if problem.isGoalState(curr[0]) is True:
              return curr[1]

          for nxt in problem.getSuccessors(curr[0]):
              q.push((nxt[0],curr[1]+[nxt[1]]))

  util.raiseNotDefined()

def uniformCostSearch(problem):
  "Search the node of least total cost first. "
  "*** YOUR CODE HERE ***"

  from util import PriorityQueue



  pq = PriorityQueue()

  pq.push(problem.getStartState(),0)

  dist = {}
  dist[problem.getStartState()] = 0

  path = {}
  path[problem.getStartState()] = []

  goal = ()

  while not pq.isEmpty():

      curr = pq.pop()

      if problem.isGoalState(curr) is True:
          goal = curr
          break

      for nxt in problem.getSuccessors(curr):
          if nxt[0] not in dist:
              dist[nxt[0]] = 2**64
          if dist[nxt[0]] > dist[curr] + nxt[2]:
              dist[nxt[0]] = dist[curr] + nxt[2]
              path[nxt[0]] = path[curr] + [nxt[1]]
              pq.push(nxt[0],dist[nxt[0]])

  return path[goal]


def nullHeuristic(state, problem=None):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided SearchProblem.  This heuristic is trivial.
  """
  return 0

def aStarSearch(problem, heuristic=nullHeuristic):
  "Search the node that has the lowest combined cost and heuristic first."
  "*** YOUR CODE HERE ***"

  from util import PriorityQueue

  try:
      corners = problem.getCorners()
      corners = heuristic(problem.getStartState(), problem)
      start = problem.getStartState()

      pq = PriorityQueue()
      pq.push(start,0)


      path = {}
      path[start] = []

      dist = {}
      dist[start] = 0

      for next_goal in corners:
          while not pq.isEmpty():
              curr = pq.pop()

              if curr == next_goal:
                  while not pq.isEmpty():
                      pq.pop()
                  pq.push(curr,0)
                  tmp = path[curr]
                  path.clear()
                  path[curr] = tmp
                  dist.clear()
                  dist[curr] = 0
                  break

              for nxt in problem.getSuccessors(curr):

                  if nxt[0] not in dist:
                      dist[nxt[0]] = 2 ** 64

                  if dist[nxt[0]] > dist[curr] + nxt[2]:
                      dist[nxt[0]] = dist[curr] + nxt[2]
                      path[nxt[0]] = path[curr] + [nxt[1]]
                      pq.push(nxt[0], dist[nxt[0]])

      return path[corners[3]]

  except:

      pq = PriorityQueue()

      pq.push(problem.getStartState(),0)

      dist = {}
      dist[problem.getStartState()] = 0

      path = {}
      path[problem.getStartState()] = []

      goal = ()

      while not pq.isEmpty():

          curr = pq.pop()

          if problem.isGoalState(curr) is True:
              goal = curr
              return path[goal]

          for nxt in problem.getSuccessors(curr):
              if nxt[0] not in dist:
                  dist[nxt[0]] = 2**64
              if dist[nxt[0]] > dist[curr] + nxt[2]:
                  dist[nxt[0]] = dist[curr] + nxt[2]
                  path[nxt[0]] = path[curr] + [nxt[1]]
                  tmp = dist[nxt[0]]+heuristic(nxt[0],problem)
                  pq.push(nxt[0],tmp)

      return path[goal]

  util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
