require 'rails'

class FileCompact
  def initialize(dir)
    @dir = dir
  end

  def call
    normalize_files(@dir)
    remove_empty_directories(@dir)
  end

  private

  def normalize_files(dir)
    Dir.glob(File.join(dir, '*')).each do |path|
      if File.file?(path)
        rename_file(path)
      elsif File.directory?(path)
        rename_folder(path)  # Renomeia a pasta primária
        normalize_files(path)
      end
    end
  end

  def rename_file(path)
    base_name = File.basename(path, '.*')
    ext_name = File.extname(path)

    new_name = "#{base_name.parameterize.gsub('_', '-')}#{ext_name}"
    new_path = File.join(File.dirname(path), new_name)

    File.rename(path, new_path)
  end

  def rename_folder(path)
    base_name = File.basename(path)

    new_name = base_name.parameterize.gsub('_', '-')
    new_path = File.join(File.dirname(path), new_name)

    File.rename(path, new_path)
  end

  def remove_empty_directories(dir)
    Dir.glob(File.join(dir, '*')).each do |path|
      if File.directory?(path)
        remove_empty_directories(path)
        Dir.rmdir(path) if Dir.empty?(path)
      end
    end
  end
end

FileCompact.new(Dir.pwd).call
