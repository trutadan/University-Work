import numpy as np

def softmax(x, t=1):
    """"
    Applies the softmax temperature on the input x, using the temperature t
    """
    # TODO your code here
    e_x = np.exp(x/t)
    return e_x / e_x.sum(axis=0)
    # end TODO your code here
