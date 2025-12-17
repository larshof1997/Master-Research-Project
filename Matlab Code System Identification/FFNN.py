# my_ffnn_onnx.py
import onnxruntime as ort
import numpy as np

# Load ONNX model (once)
MODEL_PATH = "ffnn_model.onnx"  # path to your exported ONNX
session = ort.InferenceSession(MODEL_PATH)

def predict(x_numpy):
    """
    x_numpy: numpy array of shape (6,) or (batch,6)
    returns: numpy array of shape (2,) or (batch,2)
    """
    x_np = np.array(x_numpy, dtype=np.float32)
    
    # Ensure batch dimension
    if x_np.ndim == 1:
        x_np = x_np.reshape(1, -1)
    
    # ONNX input name
    input_name = session.get_inputs()[0].name
    outputs = session.run(None, {input_name: x_np})
    
    y_np = outputs[0]
    
    # Return 1D if input was 1D
    if y_np.shape[0] == 1:
        return y_np[0]
        
    return y_np
