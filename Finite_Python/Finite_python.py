ASCII_SIZE = 256

def compute_finite_automaton(pattern):
    m = len(pattern)
    finite_automaton = [[0] * ASCII_SIZE for _ in range(m + 1)]

    for state in range(m + 1):
        for x in range(ASCII_SIZE):
            finite_automaton[state][x] = get_next_state(pattern, m, state, x)

    return finite_automaton

def get_next_state(pattern, m, state, x):
    if state < m:
        if x == ord(pattern[state]):
            return state + 1

    for next_state in range(state, 0, -1):
        if pattern[next_state - 1] == x:
            i = 0
            while i < next_state - 1:
                if pattern[i] != pattern[state - next_state + 1 + i]:
                    break
                i += 1
            if i == next_state - 1:
                return next_state

    return 0

def search_pattern(text, pattern):
    n = len(text)
    m = len(pattern)
    finite_automaton = compute_finite_automaton(pattern)
    state = 0

    for j in range(n):
        state = finite_automaton[state][ord(text[j])]
        if state == m:
            print("Pattern found at index", j - m + 1)

def main():
    try:
        with open("text.txt", "r") as text_file:
            text = text_file.readline().strip()

        with open("pattern.txt", "r") as pattern_file:
            pattern = pattern_file.readline().strip()

        search_pattern(text, pattern)

    except FileNotFoundError:
        print("Error: File not found")

if __name__ == "__main__":
    main()
