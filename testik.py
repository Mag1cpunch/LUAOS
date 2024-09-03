import tensorflow as tf
import sys

tf_version = tf.__version__

python_version = sys.version

if tf.test.is_built_with_cuda():
    cuda_version = tf.sysconfig.get_build_info()['cuda_version']
    cudnn_version = tf.sysconfig.get_build_info()['cudnn_version']
else:
    cuda_version = "Not built with CUDA"
    cudnn_version = "Not built with cuDNN"

print(f"TensorFlow version: {tf_version}")
print(f"Python version: {python_version}")
print(f"CUDA version: {cuda_version}")
print(f"cuDNN version: {cudnn_version}")
print("Num GPUs Available: ", len(tf.config.list_physical_devices('GPU')))