<?php
echo "execute the script\n";

function task()
{
    echo "callbackfunc task success\n";
}

function taskp($a, $b)
{
    var_dump($a);
    var_dump($b);
    echo "callbackfunc task success\n";
}

class T {
    static public function task()
    {
        echo "callbackfunc task on T success\n";
    }
}

$objt = new T();

// Study\Coroutine::create('T::task');
// Study\Coroutine::create('taskp', 'a', 'b');
Study\Coroutine::create(function ($a, $b){
    echo $a.PHP_EOL;
    echo $b.PHP_EOL;
}, 'a', 'b');