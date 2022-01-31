import random

def monthToday(m, y):
    if m == 4 or m == 6 or m == 9 or m == 11:
        day = 30
    elif m == 2:
        if (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0):
            day = 29
        else:
            day = 28
    else:
        day = 31

    return day



f = open('network_log(test).txt', 'a', encoding='UTF-8')

for year in range(2020, 2021):
    for mun in range(1, 12):
        print("\n\n\n" + str(year) + str(mun) + str(monthToday(mun, year)), "\n\n\n")
        for day in range(1, monthToday(mun, year), 2):
            for hour in range(0, 23, 3):
                for min in range(0, 59, 5):
                    for sec in range(0, 59, 5):
                        for ip4 in range(1, 3):
                            n = random.randint(0, 50)
                            f.write(str(year) + format(mun, '02') + format(day, '02') + format(hour, '02') + format(min, '02') + format(sec, '02') + ",192.168.1." + str(ip4) + "/24,")
                            if n < 10 or n > 40:
                                f.write("-")
                            else:
                                f.write(str(n))
                            f.write("\n")
                            print(str(year) + format(mun, '02') + format(day, '02') + format(hour, '02') + format(min, '02') + format(sec, '02') + ",192.168.1." + str(ip4) + "/24")

                        for ip3 in range(30, 33):
                            for ip4 in range(1, 3):
                                n = random.randint(0, 50)
                                f.write(str(year) + format(mun, '02') + format(day, '02') + format(hour, '02') + format(min, '02') + format(sec, '02') + ",10.20." + str(ip3) + "." + str(ip4) + "/16,")
                                if n < 10 or n > 40:
                                    f.write("-")
                                else:
                                    f.write(str(n))
                                f.write("\n")
                                print(str(year) + format(mun, '02') + format(day, '02') + format(hour, '02') + format(min, '02') + format(sec, '02') + ",10.20." + str(ip3) + "." + str(ip4) + "/16")

f.close()