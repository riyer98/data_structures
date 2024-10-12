# python3

def read_input():
    return (input().rstrip(), input().rstrip())

def print_occurrences(output):
    print(' '.join(map(str, output)))

def polyhash(string,x,prime):
    ans = 0
    for c in string:
        ans =  (ans*x + ord(c) ) % prime
    return ans


def get_occurrences(pattern, text):
    patlength = len(pattern)
    occurrences = []
    prime = 1000000007
    x = 263
    xp = x**(patlength)

    phash = polyhash(pattern,x,prime)
    thash = polyhash(text[:patlength],x,prime)

    
    for i in range(len(text)-patlength+1):
        if (phash == thash):
            if (pattern == text[i:i+patlength]): occurrences.append(i)
        
        try: thash = (thash*x - ord(text[i])*xp + ord(text[i+patlength]))% prime
        except IndexError: break
    return occurrences


if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))

