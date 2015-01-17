
**Libbase** defines useful functions for the standard types. The provided functions use the same suffixes for logically equivalent operations, and functions are separated into collections relevant to their behavior. Using the preprocessor, this allows for a crude typeclass system in C, in which some type `T` belongs to the `EQ` typeclass if the functions `T##__equal(x, y)` and `T##__not_equal(x, y)` are defined.

The utility of this approach will become evident as I publish more libraries (particularly for data structures) using Libbase.

There are header files for each of the typeclasses that provide macros that will auto-generate the source code for that typeclass for a given scalar type.


## Releases

I'll tag the releases according to [semantic versioning](http://semver.org/spec/v2.0.0.html). All the macros preceded by `// @public` are considered public: they'll only change between major versions. The other macros could change any time. Non-preprocessor identifiers defined in header files are always considered public. New identifiers prefixed with the name of the header file will not warrant a major version bump: e.g., a function `uchar__foo()` may be added to `uchar.h` between minor versions.

Every version tag will be signed with [my GPG key](http://pool.sks-keyservers.net/pks/lookup?op=vindex&search=0xD020F814) (fingerprint: `0xD020F814`).


## Dependencies

`Package.json` specifies the dependencies of Libbase: where to get them, and what version to use. I've developed a tool called [Puck](https://gitorious.org/mcinglis/puck) that will parse such a `Package.json`, download the specified repositories, check out the specified version, and, if the dependency has its own `Package.json`, repeat that process for *its* dependencies. With `puck` on your PATH, in the directory of Libbase:

``` sh
$ puck update
$ puck execute build
```

There's nothing magic to what Puck does, so if you would prefer, you can set up the dependencies manually. You just need to have the dependencies in the `deps` directory within the Libbase directory, and have them built (if necessary) before building Libbase.


## Collaboration

Libbase is available at [Gitorious](https://gitorious.org/mcinglis/libbase), [Bitbucket](https://bitbucket.org/mcinglis/libbase), and [GitHub](https://github.com/mcinglis/libbase).

Questions, discussion, bug reports and feature requests are welcome at [the GitHub issue tracker](https://github.com/mcinglis/libbase/issues), or via [emails](mailto:me@minglis.id.au).

To contribute changes, you're welcome to [email me](mailto:me@minglis.id.au) patches as per `git format-patch`, or to send me a pull request on any of the aforementioned sites. You're also welcome to just send me a link to your remote repository, and I'll merge stuff from that as I want to.

To accept notable contributions, I'll require you to assign your copyright to me. In your email/pull request and commit messages, please insert: "*I hereby irrevocably transfer to Malcolm Inglis (http://minglis.id.au) all copyrights, title, and interest, throughout the world, in these contributions to Libbase*". If you can, please sign the email or pull request, ensuring your GPG key is publicly available.


## License

**Copyright 2014 Malcolm Inglis <http://minglis.id.au>**

Libbase is free software: you can redistribute it and/or modify it under the terms of the [GNU Affero General Public License](https://gnu.org/licenses/agpl.html) as published by the [Free Software Foundation](https://fsf.org), either version 3 of the License, or (at your option) any later version.

Libbase is distributed in the hope that it will be useful, but **without any warranty**; without even the implied warranty of **merchantability** or **fitness for a particular purpose**. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with Libbase. If not, see <https://gnu.org/licenses/>.

[Contact me](mailto:me@minglis.id.au) for proprietary licensing options.

### Why AGPL?

[I believe that nonfree software is harmful](http://minglis.id.au/blog/2014/04/09/free-software-free-society.html), and I don't want to contribute to its development at all. I believe that a free society must necessarily operate on free software. I want to encourage the development of free software, and discourage the development of nonfree software.

The [GPL](https://gnu.org/licenses/gpl.html) was designed to ensure that the software stays free software; "to ensure that every user has freedom". The GPL's protections may have sufficed in 1990, but they don't in 2014. The GPL doesn't consider users of a web service to be users of the software implementing that server. Thankfully, the AGPL does.

The AGPL ensures that if Libbase is used to implement a web service, then the entire source code of that web service must be free software. This way, I'm not contributing to nonfree software, whether it's executed locally or provided over a network.
