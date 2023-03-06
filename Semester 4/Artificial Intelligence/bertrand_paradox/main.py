from random import random
from matplotlib import pyplot as plt
import numpy as np
import math


class Bertrand:
    def __init__(self):
        # create a figure and a set of subplots
        self.figure, self.axes = plt.subplots()

    @staticmethod
    def get_euclidean_distance(first_point, second_point):
        return math.sqrt((first_point[0] - second_point[0])**2 + (first_point[1] - second_point[1])**2)

    def draw_circle_for_given_radius(self, radius):
        # set the x-axis and y-axis view limits
        self.axes.set_xlim((-radius - 1, radius + 1))
        self.axes.set_ylim((-radius - 1, radius + 1))

        # set the label text for the x-axis and y-axis
        self.axes.set_xlabel('x')
        self.axes.set_ylabel('y')

        # create a circle with the center situated at (0, 0), with the given radius
        circle = plt.Circle((0, 0), radius, linewidth=5, color='black', fill=False)

        # renderer and paint the circle("artist")
        self.axes.add_artist(circle)

    def draw_equilateral_triangle(self, point):
        x, y = point

        # stack points in sequence horizontally
        points = np.hstack([x, y])
        # draw the new point on the circle
        self.axes.plot(x, y, color='grey')

        # calculate the second point of the equilateral triangle
        # rotate the point by 60 degrees to find the second point
        angle = np.deg2rad(120)
        x = point[0] * np.cos(angle) - (point[1] * np.sin(angle))
        y = point[0] * np.sin(angle) + (point[1] * np.cos(angle))
        second_point = (x, y)

        # stack points in sequence vertically
        points = np.vstack([points, [x, y]])
        # draw the new point on the circle
        self.axes.plot(x, y, color='grey')

        # calculate the second point of the equilateral triangle
        # rotate the point by 120 degrees to find the third point
        angle = np.deg2rad(240)
        x = point[0] * np.cos(angle) - (point[1] * np.sin(angle))
        y = point[0] * np.sin(angle) + (point[1] * np.cos(angle))
        third_point = (x, y)

        # stack points in sequence vertically
        points = np.vstack([points, [x, y]])
        # draw the new point on the circle
        self.axes.plot(x, y, color='grey')

        # stack points in sequence vertically
        points = np.vstack([points, [point[0], point[1]]])
        # draw the sides of the circle
        self.axes.plot(points[:, 0], points[:, 1], linewidth=5, color='grey', label='equilateral triangle')

        # side's size of the equilateral triangle
        return self.get_euclidean_distance(second_point, third_point)

    def first_approach(self, radius, number_of_chords):
        self.figure.suptitle('Bertrand paradox, 1st approach')

        # create the circle
        self.draw_circle_for_given_radius(radius)

        # generate random alpha, an angle in radians between 0 and 2π
        alpha = random() * (2 * np.pi)

        # get a fixed point on the circumference of the circle
        x, y = radius * np.cos(alpha), radius * np.sin(alpha)
        point = (x, y)

        # create the equilateral triangle
        triangle_side_size = self.draw_equilateral_triangle(point)

        favorable_cases = 0

        # generate random points on the circumference
        for i in range(number_of_chords):
            # generate random alpha for a new point
            alpha = random() * (2 * np.pi)

            # get another fixed point on the circumference of the circle
            x, y = radius * np.cos(alpha), radius * np.sin(alpha)
            another_point = (x, y)

            # plot the point on the circle
            self.axes.plot(x, y, color='black', marker='.')

            # check if the length of the chord is larger than the size of the triangle's side or not
            if self.get_euclidean_distance(point, another_point) > triangle_side_size:
                self.axes.plot([point[0], x], [point[1], y], color='red')
                favorable_cases += 1
            else:
                self.axes.plot([point[0], x], [point[1], y], color='blue')

        # display the probability
        print(f'P1 = {favorable_cases}/{number_of_chords} = {favorable_cases / number_of_chords}')

        # place the legend on the axes
        plt.legend()
        # configure the grid lines
        plt.grid()
        # display all figures
        plt.show()

    def second_approach(self, radius, number_of_chords):
        self.figure.suptitle('Bertrand paradox, 2nd approach')

        # create the circle
        self.draw_circle_for_given_radius(radius)

        # generate random alpha, an angle in radians between 0 and 2π
        alpha = random() * (2 * np.pi)

        # get a fixed point on the circumference of the circle
        x, y = radius * np.cos(alpha), radius * np.sin(alpha)

        # draw a line from the center of the circle to this point to represent the radius
        plt.plot([0, x], [0, y], color='black', linewidth=5, label='radius')

        # get a fixed point on the circumference of the circle
        x, y = radius * np.cos(alpha), radius * np.sin(alpha)
        point = (x, y)

        # create the equilateral triangle
        self.draw_equilateral_triangle(point)

        # calculate the middle point of the radius using alpha
        middle_point = r_middle_x, r_middle_y = radius / 2 * np.cos(alpha), radius / 2 * np.sin(alpha)

        # draw the middle point on the plot
        plt.plot(r_middle_x, r_middle_y, color='yellow', marker='o', label='middle of the radius')

        # perpendicular angle to alpha, used to draw chords perpendicular to the radius
        beta = abs(alpha - np.pi/2)

        favorable_cases = 0

        # generate random chords perpendicular on the radius
        for i in range(number_of_chords):
            # get a random point on the drawn radius
            m = random() * radius
            x, y = m * np.cos(alpha), m * np.sin(alpha)
            radius_point = (x, y)

            # draw the random point
            plt.plot(x, y, color='green', marker='.')

            # perpendicular line to the radius in the generated point
            x, y = radius_point

            # get the chord's length
            length = math.sqrt(radius**2 - self.get_euclidean_distance(radius_point, (0, 0))**2)

            # calculate the endpoints of a chord perpendicular to the radius at the radius point
            x1, y1 = x + length * np.cos(beta), y + length * np.sin(beta)
            x2, y2 = x - length * np.cos(beta), y - length * np.sin(beta)

            # check if the chord is inside or outside the equilateral triangle
            if self.get_euclidean_distance(middle_point, (0, 0)) < self.get_euclidean_distance(radius_point, (0, 0)):
                plt.plot([x1, x2], [y1, y2], color='red')
            else:
                plt.plot([x1, x2], [y1, y2], color='blue')
                favorable_cases += 1

        # display the probability
        print(f'P2 = {favorable_cases}/{number_of_chords} = {favorable_cases / number_of_chords}')

        # place the legend on the axes
        plt.legend()
        # configure the grid lines
        plt.grid()
        # display all figures
        plt.show()

    def third_approach(self, radius, number_of_chords):
        self.figure.suptitle('Bertrand paradox, 3rd approach')

        # create the circle
        self.draw_circle_for_given_radius(radius)

        # generate random alpha, an angle in radians between 0 and 2π
        alpha = random() * (2 * np.pi)

        # get a fixed point on the circumference of the circle
        point = radius * np.cos(alpha), radius * np.sin(alpha)

        # create the equilateral triangle
        self.draw_equilateral_triangle(point)

        # create the circle with the radius half of the initial one
        circle = plt.Circle((0, 0), radius / 2, linewidth=5, color='black', fill=False)
        self.axes.add_artist(circle)

        favorable = 0

        # generate random points inside the circle
        for i in range(number_of_chords):
            # generate random alpha for a new point
            alpha = random() * (2 * np.pi)

            # generate a random number between 0 and 1 (the point must be inside the big circle)
            rand_r = math.sqrt(random())

            # get another random point inside the circle
            x, y = rand_r * radius * np.cos(alpha), rand_r * radius * np.sin(alpha)
            new_point = (x, y)

            # check if the point lies inside the smaller circle
            # which translates to checking if its Euclidean distance from the origin is less than or equal to radius/2
            if self.get_euclidean_distance(new_point, (0, 0)) <= radius / 2:
                plt.plot(x, y, color='blue', marker='.')
                favorable += 1
            else:
                plt.plot(x, y, color='red', marker='.')

        # display the probability
        print(f'P3 = {favorable}/{number_of_chords} = {favorable / number_of_chords}')

        # place the legend on the axes
        plt.legend()
        # configure the grid lines
        plt.grid()
        # display all figures
        plt.show()


def main():
    try:
        radius = float(input('the radius = '))
        number_of_chords = int(input('the number of simulated chords = '))
    except ValueError:
        print("Wrong type provided!")
        return

    bertrand_paradox = Bertrand()
    bertrand_paradox.first_approach(radius, number_of_chords)

    bertrand_paradox = Bertrand()
    bertrand_paradox.second_approach(radius, number_of_chords)

    bertrand_paradox = Bertrand()
    bertrand_paradox.third_approach(radius, number_of_chords)


if __name__ == '__main__':
    main()
