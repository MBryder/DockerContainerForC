# Use an official GCC image as the base image
FROM gcc:latest

# Set the working directory
WORKDIR /workspace

# Install any additional packages if needed
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Copy the current directory contents into the container at /workspace
COPY . /workspace
