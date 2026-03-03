function mysfunc(block)
    setup(block);
end

function setup(block)

    % No inputs
    block.NumInputPorts = 0;

    % One output
    block.NumOutputPorts = 1;
    block.OutputPort(1).Dimensions = 1;
    block.OutputPort(1).SamplingMode = 'Sample';

    % Sample time
    block.SampleTimes = [0.001 0];

    block.RegBlockMethod('Outputs', @Outputs);
end

function Outputs(block)
    % Example output
    t = block.CurrentTime;
    block.OutputPort(1).Data = sin(2*pi*t);
end
