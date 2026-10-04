apt update
apt install wget curl bzip2 build-essential tar git python3 -y
git clone "https://github.com/vitasdk/vdpm.git"
sed -i "s/sudo //g" ./vdpm/include/install-vitasdk.sh
./vdpm/bootstrap-vitasdk.sh && ./vdpm/install-all.sh