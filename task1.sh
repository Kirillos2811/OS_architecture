mkdir attachments
for ((i = 0; i < 20; i++))
do
	touch "attachments/image$i"
	curl https://picsum.photos/800/400 -L > "attachments/image$i"
done