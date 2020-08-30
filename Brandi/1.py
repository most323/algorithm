
if __name__ == '__main__':
    age = int(input())

    max_hearth_rate = 220 - age

    answer = [0 for i in range(6)]
    while True:
        try:
            user_input = input()
        except:
            break
        hearth_rate = int(user_input)

        rate = (hearth_rate/max_hearth_rate * 100)

        if rate < 60:
            answer[0] += 1
        elif rate < 68:
            answer[1] += 1
        elif rate < 75:
            answer[2] += 1
        elif rate < 80:
            answer[3] += 1
        elif rate < 90:
            answer[4] += 1
        else:
            answer[5] += 1

    for item in answer[::-1]:
        print(item, end=" ")

