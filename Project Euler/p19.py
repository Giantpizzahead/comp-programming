day = 1
month = 1
year = 1900

def is_leap_year(y):
    return y % 4 == 0 and (y % 100 != 0 or y % 400 == 0)

def days_in_month(m):
    lookup = [-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if m == 2 and is_leap_year(year):
        return 29
    else:
        return lookup[m]

def advance_day():
    global day, month, year
    if day == days_in_month(month):
        if month == 12:
            month = 1
            year += 1
        else:
            month += 1
        day = 1
    else:
        day += 1

def advance_days(x):
    for i in range(x):
        advance_day()

# Go to Sunday
advance_days(6)
while year < 1901:
    advance_days(7)
num_sundays = 0
while year <= 2000:
    if day == 1:
        num_sundays += 1
    advance_days(7)

print(num_sundays)
