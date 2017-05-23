import os
import sys
import time
import random
import string
import signal

import pexpect

def main():
    err = open("errors.txt", "w")
    sys.stdout = err
    sys.stderr = err

    # generate a new seed with no args
    if len(sys.argv) == 1:
	with open("seed.txt", "w") as out:
            seed = int(time.time())
            out.write(str(seed))

    # or run the students executable when provided
    else:
        # script run python test_bytes.py ./studentdriver
        run_with_gdb("gdb", sys.argv[1], "gdbOutput.txt", False)


    err.close()

    return 0


def clean_cmd_output(cmd_out):
    cmd_out = cmd_out.strip()
    return "\n".join([line.rstrip() for line in cmd_out.split("\n")])


def run_with_gdb(gdb_cmd, sol_name, outpt_name, prof_mode):
    all_outpt = ""

    with open(outpt_name, "w") as outpt:
        outpt.write("Trying to run your code in gdb...\n")
        outpt.write("This part isn't graded, it just gives more informtion.\n")
        outpt.write("\n")

        cmd = " ".join([gdb_cmd, sol_name])
        num_tests = int(simple_run(" ".join([sol_name, "--tests"])))

        for test in range(num_tests):
 
            p = pexpect.spawn(cmd)
            p.setecho(False)

            if prof_mode:
                run_cmd =  " ".join(["run", "--prof", str(test)])

            else:
                run_cmd = " ".join(["run", str(test)])

            try: 

                # when gdb first start up
                p.expect("\(gdb\)", timeout=5)
                all_outpt += "(gdb) "
                all_outpt += run_cmd + "\n"

                # run the right test      
                p.sendline(run_cmd)

                # should see another prompt
                p.expect("\(gdb\)", timeout=5)
                all_outpt += clean_cmd_output(p.before)

                # try to quit gracefully
                p.sendline("quit")
                m = p.expect([pexpect.EOF, "\(y or n\)"], timeout=5)

                # if it doesn't want us to quit
                if m == 1:
                    p.sendline("y")  
                    p.expect(pexpect.EOF, timeout=5)

                all_outpt += clean_cmd_output(p.before) + "\n\n"
                p.close(force=True)

            except pexpect.ExceptionPexpect:
                # clean up any extra processes
                ps = simple_run("ps -a")

                for line in ps.split("\n")[1:]:
                    if os.path.splitext(os.path.basename(sol_name))[0] in line:
                       os.kill(int(line.split()[0]), signal.SIGKILL)

        outpt.write(all_outpt)
    

def run_program(sol_name, prof_mode):
    num_tests = int(simple_run(" ".join([sol_name, "--tests"])))

    for test in range(num_tests):
        if prof_mode:
            cmd =  " ".join([sol_name, "--prof", str(test)])

        else:
            cmd = " ".join([sol_name, str(test)])

	simple_run(cmd)
 

def simple_run(cmd):
    all_output = ""

    p = pexpect.spawn(cmd)
    p.setecho(False)

    try: 
        p.expect(pexpect.EOF)

    finally:
        all_output += clean_cmd_output(p.before)
        p.close(force=True)

    return all_output


if __name__ == "__main__":
    main()
