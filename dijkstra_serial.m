
filename = 'graph_data.txt';

% 1.  (Read Metadata)
fileID = fopen(filename, 'r');
header = fgetl(fileID);
fclose(fileID);
meta = sscanf(header, '%d %d');
num_nodes = meta(1);

% 2. (Read edge data)
data = readmatrix(filename, 'NumHeaderLines', 1);

% 3.  (Build Graph)
% Python 是 0 索引，Matlab 是 1 索引，所以 +1
s = data(:, 1) + 1; 
t = data(:, 2) + 1;
weights = data(:, 3);
G = digraph(s, t, weights);

% 4.  (Calculate Distances)

dist_results = distances(G, 1); 

% 5.  (Print first 5 results)
fprintf('\n--- Matlab Reference ---\n');
for i = 1:min(5, num_nodes)
    fprintf('Distance to node %d: %g\n', i-1, dist_results(i));
end
