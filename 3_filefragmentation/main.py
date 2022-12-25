import sys


def check_single_bucket(bucket, solution):
    remaining = list(bucket)

    while remaining:
        current = remaining.pop()

        counter = [
            i
            for i in range(len(remaining))
            if current + remaining[i] == solution or remaining[i] + current == solution
        ]

        if len(counter) == 0:
            return False

        del remaining[counter[0]]

    return True


def check_solution(buckets, solution):
    for i in range(len(buckets) // 2):
        bucket = buckets[i]
        counter_bucket = buckets[len(solution) - i]

        used_counters = set()
        for fragment in bucket:
            counter_fragment = [
                j
                for j in range(len(counter_bucket))
                if j not in used_counters
                and fragment + counter_bucket[j] == solution
                or counter_bucket[j] + fragment == solution
            ]

            if len(counter_fragment) == 0:
                return False

            used_counters.add(counter_fragment[0])

    if len(solution) % 2 == 0:
        return check_single_bucket(buckets[len(solution) // 2], solution)

    return True


def solve_case(fragments):
    result_len = sum(len(x) for x in fragments) * 2 // len(fragments)

    buckets = [[] for _ in range(result_len + 1)]

    for f in fragments:
        buckets[len(f)].append(f)

    first_fragment = fragments[0]

    for second_fragment in buckets[result_len - len(first_fragment)]:
        sol1 = first_fragment + second_fragment
        if check_solution(buckets, sol1):
            return sol1

        sol2 = second_fragment + first_fragment
        if check_solution(buckets, sol2):
            return sol2

    raise Exception("no solution")


def main():
    # with open(
    #     "/Users/vgriebel/Documents/proseminar_pa/3_filefragmentation/input.txt"
    # ) as fs:
    #     lines = fs.readlines()

    lines = list(sys.stdin)
    cases = int(lines[0])

    pos = 2

    for i in range(cases):
        fragments = []

        while True:
            fragments.append(lines[pos].strip())
            pos += 1

            if pos == len(lines):
                break

            if not lines[pos].strip():
                pos += 1
                break

        solution = solve_case(fragments)

        if i > 0:
            print()
        print(solution, end="")


main()
