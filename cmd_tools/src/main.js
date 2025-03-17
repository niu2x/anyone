#!/usr/bin/env node

import path from "path"
import fs from "fs";

import {
  fileURLToPath
} from 'url';

import {
  dirname
} from 'path';

import {
  spawn
} from 'node:child_process';

import {
  Command
} from 'commander';

const __filename = fileURLToPath(
  import.meta.url);
const __dirname = dirname(__filename);
const anyone_rt = path.join(__dirname, "../../build/anyone_rt")

function waitWork(worker) {
  return new Promise((resolve, reject) => {
    worker.stdout.on('data', (data) => {
      process.stdout.write(data);
    });

    let forward_stdin = (data) => {
      worker.stdin.write(data);
    };
    process.stdin.on('data', forward_stdin);

    worker.stderr.on('data', (data) => {
      process.stderr.write(data);
    });

    worker.on('close', (code) => {
      process.stdin.off('data', forward_stdin);
      process.stdin.pause();

      if (code !== 0) {
        reject({
          exitCode: code
        })
      } else {
        resolve()
      }
    });
  })
}

const program = new Command();

program
  .name('anyone')

program.command("init")
  .argument('<dir>', 'project directory')
  .action((dir) => {
    const configPath = path.join(dir, "project.json")
    const projectConfig = {
      "name": "Anyone Game",
      "entry": "entry.lua"
    }
    fs.writeFileSync(configPath, JSON.stringify(projectConfig, null, "  "))
  })

program.command("run")
  .argument('[dir]', 'project directory')
  .action(async (dir) => {
    if (dir == undefined) {
      dir = "./"
    }
    const worker = spawn(anyone_rt,
      ['--project', dir]);
    await waitWork(worker);
  })

// registerSubCommand(program)
program.parse(process.argv);