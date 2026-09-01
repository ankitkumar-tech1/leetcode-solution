from collections import deque
from typing import List

class Solution:
    def minMoves(self, classroom: List[str], energy: int) -> int:
        m, n = len(classroom), len(classroom[0])
        litter_index = {}
        start = None
        numL = 0

        # Assign litter bits
        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'S':
                    start = (i, j)
                elif classroom[i][j] == 'L':
                    litter_index[(i, j)] = numL
                    numL += 1

        if numL == 0:
            return 0

        target_mask = (1 << numL) - 1

        # visited[x][y][mask] = max energyLeft seen
        visited = [[[-1] * (1 << numL) for _ in range(n)] for _ in range(m)]
        sx, sy = start
        visited[sx][sy][0] = energy

        q = deque()
        q.append((sx, sy, 0, energy, 0))  # x,y,mask,energyLeft,moves

        while q:
            x, y, mask, eLeft, moves = q.popleft()
            if mask == target_mask:
                return moves

            for dx, dy in [(1,0),(-1,0),(0,1),(0,-1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and classroom[nx][ny] != 'X':
                    if eLeft <= 0:
                        continue
                    newEnergy = eLeft - 1
                    newMask = mask
                    if classroom[nx][ny] == 'R':
                        newEnergy = energy
                    if (nx, ny) in litter_index:
                        newMask |= 1 << litter_index[(nx, ny)]
                    if newEnergy > visited[nx][ny][newMask]:
                        visited[nx][ny][newMask] = newEnergy
                        q.append((nx, ny, newMask, newEnergy, moves + 1))

        return -1
