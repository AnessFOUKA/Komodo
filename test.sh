read -p "test value" $test
if [ "$test" -eq 5 ]; then
    echo "test"
else
    echo "fail"
fi