#cd input_files
for d in user.ebusch.*; do
	echo  "hadd ${d%.v11p1_output.root}.root $d/user.ebusch.*"
	hadd ${d%.v11p1_output.root}.root $d/user.ebusch.*
done 
#cd ..
