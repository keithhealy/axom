#!/usr/local/bin/python
###############################################################################
# 
###############################################################################

"""
 file: llnl_lc_uberenv_install_tools.py

 description: 
  helpers for installing toolkit tpls on llnl lc systems.

"""

import os
import sys
import subprocess
import datetime
import glob
import json

from os.path import join as pjoin

def sexe(cmd,
         ret_output=False,
         output_file = None,
         echo = False):
    """ Helper for executing shell commands. """
    if echo:
        print "[exe: %s]" % cmd
    if ret_output:
        p = subprocess.Popen(cmd,
                             shell=True,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        res =p.communicate()[0]
        return p.returncode,res
    elif output_file != None:
        ofile = open(output_file,"w")
        p = subprocess.Popen(cmd,
                             shell=True,
                             stdout= ofile,
                             stderr=subprocess.STDOUT)
        res =p.communicate()[0]
        return p.returncode
    else:
        rcode = subprocess.call(cmd,shell=True)
        if rcode != 0:
            print "{ERROR [return code: %d] from command: %s}" % (rcode,cmd)
        return rcode

def timestamp(t=None,sep="_"):
    """ Creates a timestamp that can easily be included in a filename. """
    if t is None:
        t = datetime.datetime.now()
    sargs = (t.year,t.month,t.day,t.hour,t.minute,t.second)
    sbase = "".join(["%04d",sep,"%02d",sep,"%02d",sep,"%02d",sep,"%02d",sep,"%02d"])
    return  sbase % sargs

def build_info():
    res = {}
    res["built_by"] = os.environ["USER"]
    res["built_from_branch"] = "unknown"
    res["built_from_sha1"]   = "unknown"
    rc, out = sexe('git branch -a | grep \"*\"',ret_output=True)
    out = out.strip()
    if rc == 0 and out != "":
        res["built_from_branch"]  = out.split()[1]
    rc,out = sexe('git rev-parse --verify HEAD',ret_output=True)
    out = out.strip()
    if rc == 0 and out != "":
        res["built_from_sha1"] = out
    return res

def write_build_info(ofile):
    print "[build info]"
    binfo_str = json.dumps(build_info(),indent=2)
    print binfo_str
    open(ofile,"w").write(binfo_str)

def uberenv_create_mirror(prefix,mirror_path):
    """
    Calls uberenv to create a spack mirror.
    """
    cmd = "python ../uberenv.py --prefix %s --mirror %s --create-mirror " % (prefix,mirror_path)
    return sexe(cmd,echo=True)


def uberenv_install_tpls(prefix,spec,mirror = None):
    """
    Calls uberenv to install tpls for a given spec to given prefix.
    """
    cmd = "python ../uberenv.py --prefix %s --spec %s " % (prefix,spec)
    if not mirror is None:
        cmd += "--mirror %s" % mirror
    return sexe(cmd,echo=True)

def patch_host_configs(prefix):
    """
    Sanity check that looks for host config files generated at 
    the given prefix. 
    """
    # load manual edits into a dict with keys that we can compare to 
    # generated host config names
    manual_edits_pattern = os.path.abspath(pjoin("../../../host-configs/*manual.edits.txt"))
    manual_edits_files = glob.glob(manual_edits_pattern)
    manual_edits = {}
    for f in manual_edits_files:
        base = os.path.basename(f)[:-(len("manual.edits.txt")+1)]
        manual_edits[base] = open(f).read()
    # loop over 
    fs = glob.glob(pjoin(prefix,"*.cmake"))
    print "[found %d host config files @ %s]" % (len(fs),prefix)
    for f in fs:
        print "[ -> %s  ]" %  f
        for me_key in manual_edits.keys():
            # see if the key matches
            if f.count(me_key) == 1:
                # make sure the text wasn't already appended
                patch_txt = manual_edits[me_key]
                host_cfg_txt = open(f).read()
                if not patch_txt in host_cfg_txt:
                    # append the manual edits
                    print "[patching %s with manual edits for %s]" % (f,me_key)
                    ofile = open(f,"w")
                    ofile.write(host_cfg_txt)
                    ofile.write(patch_txt)
                    ofile.write("\n")

############################################################
# helpers for testing a set of host configs
############################################################

def build_and_test_host_config(test_root,host_config):
    host_config_root = os.path.splitext(os.path.basename(host_config))[0]
    # setup build and install dirs
    build_dir   = pjoin(test_root,"build-%s"   % host_config_root)
    install_dir = pjoin(test_root,"install-%s" % host_config_root)
    # configure
    sexe("python ../../config-build.py  -bp %s -ip %s -hc %s" % (build_dir,install_dir,host_config),
         echo=True)
    ####
    # build, test, and install
    ####
    sexe("cd %s && make -j 8 " % build_dir,
         output_file = pjoin(build_dir,"output.log.make.txt"),
         echo=True)

    sexe("cd %s && make test " % build_dir,
         output_file = pjoin(build_dir,"output.log.make.test.txt"),
         echo=True)

    sexe("cd %s && make install " % build_dir,
         output_file = pjoin(build_dir,"output.log.make.install.txt"),
         echo=True)

    # simple sanity check for make install
    print "[checking install dir %s]" % install_dir 
    sexe("ls %s/bin" %     install_dir, echo=True)
    sexe("ls %s/docs" %    install_dir, echo=True)
    sexe("ls %s/include" % install_dir, echo=True)
    sexe("ls %s/lib" %     install_dir, echo=True)


def build_and_test_host_configs(prefix):
    host_configs = glob.glob(pjoin(prefix,"*.cmake"))
    if len(host_configs) > 0:
        test_root =  pjoin(prefix,"_asctk_build_and_test_%s" % timestamp())
        os.mkdir(test_root)
        write_build_info(pjoin(test_root,"info.json")) 
        for host_config in host_configs:
            build_and_test_host_config(test_root,host_config)
    else:
        print "[error no host configs found at %s]" % prefix


def set_toolkit_group_and_perms(directory):
    """
    Sets the proper group and access permissions of given input
    directory. 
    """
    print "[changing group and access perms of: %s]" % directory
    # change group to toolktid
    print "[changing group to toolkitd]"
    sexe("chgrp -f -R toolkitd  %s" % (directory),echo=True)
    # change group perms to rwX
    print "[changing perms for toolkitd members to rwX]"
    sexe("chmod -f -R g+rwX  %s" % (directory),echo=True)
    # change perms for all to rX
    print "[changing perms for all users to rX]"
    sexe("chmod -f -R a+rX  %s" % (directory),echo=True)




