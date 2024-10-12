# python3

from collections import deque

def max_sliding_window_improved(sequence, m):
    maximums = []
    ##initializing dequeue
    q = deque([0])
    for i in range(1,m):
        while (len(q)!=0 and sequence[q[-1]]<=sequence[i]): 
            q.pop()
        q.append(i)

    for i in range(m,n):
        maximums.append(sequence[q[0]])
        if (q[0]==i-m): q.popleft()
        while (len(q)!=0 and sequence[q[-1]]<=sequence[i]): 
            q.pop()
        q.append(i)
    maximums.append(sequence[q.popleft()])

    return maximums

if __name__ == '__main__':
    n = int(input())
    input_sequence = [int(i) for i in input().split()]
    assert len(input_sequence) == n
    window_size = int(input())

    print(*max_sliding_window_improved(input_sequence, window_size))

